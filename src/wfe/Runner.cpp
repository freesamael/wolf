/**
 * \file Runner.cpp
 * \date Apr 1, 2010
 * \author samael
 */

#include <iostream>
#include <string>
#include <deque>
#include <cstdlib>
#include "Thread.h"
#include "UDPSocket.h"
#include "TLVReaderWriter.h"
#include "HelperMacros.h"
#include "Runner.h"
#include "D2MCE.h"
#include "internal/RunnerSideMasterConnector.h"
#include "internal/RunnerSideConnectionListener.h"
#include "internal/RunnerSideCommandListener.h"
#include "internal/RunnerSideCommandSender.h"
#include "internal/RunnerSideWorkerExecutor.h"

using namespace std;
using namespace cml;

namespace wfe
{

struct PData
{
	PData(): pmsock(NULL), pmclis(NULL), pmclthread(NULL), pcnlis(NULL),
			rsocks(), rclis(), rclthreads(), cmdsdr(), pwexe(NULL),
			pwexethread(NULL), wq(), wqmx(), wmsc(0), wmscmx() {}
	// Master related resources.
	TCPSocket *pmsock;							// Master sock.
	RunnerSideCommandListener *pmclis;			// Master cmd listener.
	Thread *pmclthread;							// Master cmd listen thread.

	// Runner related resources.
	RunnerSideConnectionListener *pcnlis;		// Runner connection listener.
	vector<TCPSocket *> rsocks;					// Runner socks.
	vector<RunnerSideCommandListener *> rclis;	// Runner cmd listeners.
	vector<Thread *> rclthreads;				// Runner cmd listener threads.

	// Others.
	RunnerSideCommandSender cmdsdr;				// Command sender.
	RunnerSideWorkerExecutor *pwexe;			// Worker executor.
	Thread *pwexethread;						// Worker execution thread.
	deque<pair<uint32_t, AbstractWorkerActor *> > wq;	// Working queue.
	Mutex wqmx;									// Working queue mutex.
	int wmsc;									// Worker miss count.
	Mutex wmscmx;								// Worker miss count mutex.
};

Runner::Runner(uint16_t master_port, uint16_t runner_port,
		const string &appname): _state(NOT_READY), _statemx(), _statewcond(),
		_mport(master_port), _rport(runner_port), _appname(appname), _rsock(),
		_d(new PData())
{
	_rsock.setAutoclean(false);
}

Runner::~Runner()
{
	// Cleanup all workers.
	deque<pair<uint32_t, AbstractWorkerActor *> >::iterator iter;
	for (iter = _d->wq.begin(); iter != _d->wq.end(); iter++)
		delete iter->second;

	// Cleanup worker executor.
	delete _d->pwexethread;
	delete _d->pwexe;

	// Cleanup master command listener and socket.
	delete _d->pmclthread;
	delete _d->pmclis;
	delete _d->pmsock;

	// Cleanup runner connection listener.
	delete _d->pcnlis;

	// Cleanup runner command listeners and sockets.
	for (unsigned i = 0; i < _d->rsocks.size(); i++) {
		delete _d->rclthreads[i];
		delete _d->rclis[i];
		delete _d->rsocks[i];
	}

	delete _d;
}

void Runner::run()
{
	_statemx.lock();
	if (_state != NOT_READY) {
		_statemx.unlock();
		PERR("Invalid operation.");
		return;
	}
	_statemx.unlock();

	// Connect to master and join D2MCE.
	RunnerSideMasterConnector msconn;
	if (!(_d->pmsock = msconn.connect(_mport, _rport))) {
		PERR("Runner fails. Exit.");
		return;
	}
	_d->cmdsdr.joinD2MCE(_d->pmsock, _appname);

	// Start listening connections from other runners.
	PINF_2("Starting runner connection listener.");
	_d->pcnlis = new RunnerSideConnectionListener(this, &_rsock, _rport);
	_d->pcnlis->start();

	// Start listening master commands.
	PINF_2("Starting master command listener.");
	_d->pmclis = new RunnerSideCommandListener(this, _d->pmsock);
	_d->pmclthread = new Thread(_d->pmclis);
	_d->pmclthread->start();

	// Create worker executor and corresponding thread (but not start yet).
	_d->pwexe = new RunnerSideWorkerExecutor(this);
	_d->pwexethread = new Thread(_d->pwexe);

	// Send hello message to master.
	_d->cmdsdr.hello(_d->pmsock);

	// Set to ready and wait until ends.
	_statemx.lock();
	_state = READY;
	_statewcond.wait(&_statemx);
	_statemx.unlock();
	_d->pmclthread->join();
	PINF_2("Runner ends.");
}

/**
 * Connect to a runner with given address.
 */
void Runner::connectRunner(const HostAddress &addr)
{
	TCPSocket *sock = new TCPSocket();
	if (sock->activeOpen(addr, _rport)) {
		runnerConnected(sock);
		_d->cmdsdr.hello(sock);
	} else {
		PERR("Unable to connect to the runner at " << addr.toString());
	}
}

/**
 * Called when a runner connection got.
 */
void Runner::runnerConnected(TCPSocket *runnersock)
{
	RunnerSideCommandListener *lis =
			new RunnerSideCommandListener(this, runnersock);
	Thread *listhread = new Thread(lis);

	PINF_2("Starting runner command listener.");
	listhread->start();

	_d->rsocks.push_back(runnersock);
	_d->rclis.push_back(lis);
	_d->rclthreads.push_back(listhread);
}

/**
 * Start accepting commands and stop listening for runner connections.
 */
void Runner::startWorking()
{
	_statemx.lock();
	if (_state != READY) {
		_statemx.unlock();
		PERR("Invalid operation.");
		return;
	}
	_statemx.unlock();

	PINF_2("Stopping runner connection listener.");
	_d->pcnlis->stop();
	PINF_2("Totally " << _d->rsocks.size() << " runners connected.");

	PINF_2("Starting worker executor.");
	_d->pwexethread->start();

	_statemx.lock();
	_state = WORKING;
	_statemx.unlock();
}

/**
 * Add a worker into the waiting queue for execution.
 */
void Runner::putWorker(uint32_t wseq, AbstractWorkerActor *worker)
{
	_d->wqmx.lock();
	_d->wq.push_back(pair<uint32_t, AbstractWorkerActor *>(wseq, worker));
	_d->wmscmx.lock();
	_d->wmsc = 0;
	_d->wmscmx.unlock();
	_d->wqmx.unlock();
}

/**
 * Take a worker from the waiting queue.
 */
pair<uint32_t, AbstractWorkerActor *> Runner::takeWorker()
{
	pair<uint32_t, AbstractWorkerActor *> w(0, NULL);

	_d->wqmx.lock();
	if (_d->wq.size() > 0) {
		w = _d->wq.front();
		_d->wq.pop_front();
	}
	_d->wqmx.unlock();

	if (!w.second)
		workerMissed();

	return w;
}

/**
 * Notify that a worker has been finished.
 */
void Runner::workerFinished(uint32_t wseq, AbstractWorkerActor *worker)
{
	_d->cmdsdr.workerFinished(_d->pmsock, wseq, worker);
	delete worker;
}

/**
 * Called when takeWorker() returns NULL.
 */
void Runner::workerMissed()
{
	int tc;

	_d->wmscmx.lock();
	tc = ++_d->wmsc;
	_d->wmscmx.unlock();

	// Random steal each time count increases 10 times.
	if (tc >= 10 && ((tc % 10) == 0)) {
		int index = rand() % _d->rsocks.size();
		_d->cmdsdr.stealWorker(_d->rsocks[index]);
	}
}

/**
 * Send a worker (if any) to given runner.
 */
void Runner::sendWorker(TCPSocket *sock)
{
	pair<uint32_t, AbstractWorkerActor *> wp = takeWorker();
	if (wp.second) {
		_d->cmdsdr.runWorker(sock, wp.first, wp.second);
		delete wp.second;
	} else {
		PINF_2("No worker to send. Skipping.");
	}
}

/**
 * Stop the runner.
 */
void Runner::shutdown()
{
	_statemx.lock();
	if (_state == READY) {
		_statemx.unlock();
		PINF_2("Stopping runner connection listeners.");
		_d->pcnlis->stop();
	} else if (_state == WORKING) {
		_statemx.unlock();
		PINF_2("Stopping worker executor.");
		_d->pwexe->setDone();
		_d->pwexethread->join();
	} else {
		_statemx.unlock();
		PERR("Invalid operation.");
		return;
	}

	PINF_2("Closing all runner sockets.");
	for (unsigned i = 0; i < _d->rsocks.size(); i++)
		_d->rsocks[i]->close();

	PINF_2("Stopping all runner command listeners.");
	for (unsigned i = 0; i < _d->rclis.size(); i++)
		_d->rclis[i]->setDone();

	PINF_2("Wait until all runner command listeners end.");
	for (unsigned i = 0; i < _d->rclthreads.size(); i++)
		_d->rclthreads[i]->join();

	PINF_2("Closing master socket.");
	_d->pmsock->close();

	PINF_2("Stopping master command listener.");
	_d->pmclis->setDone();

	_statemx.lock();
	_state = END;
	_statewcond.wakeAll();
	_statemx.unlock();
}

}
