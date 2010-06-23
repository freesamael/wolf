/**
 * \file Master.cpp
 * \date Apr 1, 2010
 * \author samael
 */

#include <sys/time.h>
#include <unistd.h>
#include <cstdlib>
#include "Mutex.h"
#include "UDPSocket.h"
#include "TLVReaderWriter.h"
#include "Thread.h"
#include "SingletonAutoDestructor.h"
#include "TLVUInt32.h"
#include "Master.h"
#include "TLVCommand.h"
#include "ManagerActor.h"
#include "internal/MasterSideConnectionListener.h"
#include "internal/MasterSideCommandListener.h"
#include "internal/MasterSideCommandSender.h"

using namespace std;
using namespace cml;

namespace wfe
{

struct PData
{
	PData(): rsocks(), clis(), clthreads(), rsocksmx(), cmdsdr(), mgrq(),
			mgrqmx(), bcastaddr(HostAddress::BroadcastAddress), bcastttl(1) {}

	vector<TCPSocket *> rsocks;					// Runner sockets.
	vector<MasterSideCommandListener *> clis;	// Command listeners.
	vector<Thread *> clthreads;					// Command listener threads.
	Mutex rsocksmx;								// Runner sockets mutex.

	MasterSideCommandSender cmdsdr;				// Command sender.
	map<uint32_t, ManagerActor *> mgrq;			// Manager queue.
	Mutex mgrqmx;								// Manager queue mutex.
	HostAddress bcastaddr;						// Broadcast address.
	int bcastttl;								// Broadcast TTL.
};

SINGLETON_REGISTRATION(Master);
SINGLETON_DEPENDS_SOCKET(Master);
SINGLETON_REGISTRATION_END();

const string Master::StateString[] = { "Not Ready", "Ready", "End" };

Master::Master():
		SINGLETON_MEMBER_INITLST,	_state(NOT_READY), _msock(), _defdisp(),
		_activedisp(&_defdisp), _d(new PData)
{
}

Master::~Master()
{
	for (unsigned i = 0; i < _d->clis.size(); i++)
		delete _d->clis[i];
	for (unsigned i = 0; i < _d->clthreads.size(); i++)
		delete _d->clthreads[i];
	delete _d;
}

/**
 * Initial master with program parameters.
 */
void Master::init(int argc, char *argv[])
{
	int opt;
	while ((opt = getopt(argc, argv, "a:t:")) != -1) {
		switch (opt) {
		case 'a':
			_d->bcastaddr = HostAddress(optarg);
			PINF_2("Broadcast address will be " << _d->bcastaddr.toString());
			break;
		case 't':
			_d->bcastttl = atoi(optarg);
			PINF_2("Broadcast TTL will be " << _d->bcastttl);
			break;
		default:
			cerr << "Usage: " << argv[0] <<
			" [-a broadcast_address] [-t broadcast_ttl]" << endl;
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * Setup the master. It must be called before other operations.
 */
bool Master::setup(uint16_t master_port, uint16_t runner_port,
		const string &appname, unsigned int timeout)
{
	if (_state != NOT_READY)
		return false;

	// Start waiting runner connections.
	MasterSideConnectionListener listener(this, &_msock, master_port);
	listener.start();

	// Join D2MCE group and broadcast hello message.
	_d->cmdsdr.joinD2MCE(appname);
	_d->cmdsdr.hello(runner_port, _d->bcastaddr, _d->bcastttl);

	// Check the runners.
	sleep(timeout);
	listener.stop();
	if (_d->rsocks.size() == 0) {
		PERR("No runner found.");
		return false;
	}

	// Bind command listeners to each runner, and start all runners.
	for (unsigned i = 0; i < _d->rsocks.size(); i++) {
		MasterSideCommandListener *cl =
				new MasterSideCommandListener(this, _d->rsocks[i]);
		Thread *clth = new Thread(cl);
		clth->start();
		_d->clis.push_back(cl);
		_d->clthreads.push_back(clth);
		_d->cmdsdr.startRunner(_d->rsocks[i]);
	}

	_state = READY;
	return true;
}

/**
 * Send a worker out to run.
 */
void Master::runWorker(AbstractWorkerActor *worker, ManagerActor *mgr)
{
	if (!worker || !mgr)
		return;

#ifndef DISABLE_D2MCE
	_d->mgrqmx.lock();
	for (unsigned i = 0; i < _d->rsocks.size(); i++) {
		uint32_t seq = _d->cmdsdr.runWorker(_d->rsocks[i], worker);
		_d->mgrq[seq] = mgr;
		PINF_2("Queue size = " << _d->mgrq.size());
	}
	_d->mgrqmx.unlock();
#else
	_d->rsocksmx.lock();
	TCPSocket *runner = dispatcher()->choose(_d->rsocks);
	_d->rsocksmx.unlock();
	if (runner) {
		_d->mgrqmx.lock();
		uint32_t seq = _d->cmdsdr.runWorker(runner, worker);
		_d->mgrq[seq] = mgr;
		PINF_2("Queue size = " << _d->mgrq.size());
		_d->mgrqmx.unlock();
	}
#endif /* DISABLE_D2MCE */
}

/**
 * Tell the runners to shutdown. It should be perform before program exits.
 */
void Master::shutdown()
{
	// Shutdown all runners and stop all command listeners.
	for (unsigned i = 0; i < _d->rsocks.size(); i++) {
		_d->cmdsdr.shutdown(_d->rsocks[i]);
		_d->clis[i]->setDone();
	}

	// Wait listener threads end.
	for (unsigned i = 0; i < _d->clthreads.size(); i++)
		_d->clthreads[i]->join();

	_state = END;
}

/**
 * Used by RunnerCommandListener to notify that a runner is got.
 */
void Master::runnerConnected(cml::TCPSocket *runnersock)
{
	PINF_2("Got one runner.");
	vector<HostAddress> addrs;
	_d->rsocksmx.lock();
	for (unsigned i = 0; i < _d->rsocks.size(); i++) {
		addrs.push_back(_d->rsocks[i]->peerAddress());
	}
	_d->cmdsdr.addRunner(runnersock, addrs);
	_d->rsocks.push_back(runnersock);
	_d->rsocksmx.unlock();
}

/**
 * Notify Master that a worker has finished.
 */
void Master::workerFinished(uint32_t wseq, const AbstractWorkerActor &worker)
{
	PINF_2("Worker " << wseq << " finished.");

	// Find the belonging manager.
	map<uint32_t, ManagerActor *>::iterator iter;
	_d->mgrqmx.lock();
	if ((iter = _d->mgrq.find(wseq)) == _d->mgrq.end()) {
		PERR("No manager found owning worker with sequence = " << wseq);
		return;
	}

	// Take the value and remove the manager from the queue.
	ManagerActor *mgr = iter->second;
	_d->mgrq.erase(iter);
	_d->mgrqmx.unlock();

#ifndef DISABLE_D2MCE
	// Check if it's the last worker owned by that manager.
	map<uint32_t, ManagerActor *>::iterator tmpiter;
	bool lastone = true;
	_d->mgrqmx.lock();
	for (tmpiter = _d->mgrq.begin();
			tmpiter != _d->mgrq.end(); ++tmpiter) {
		if (tmpiter->second == mgr) {
			lastone = false;
			break;
		}
	}
	_d->mgrqmx.unlock();

	// Notify manager only if it's the last worker.
	if (lastone) {
		PINF_2("Notifying manager.");
		mgr->workerFinished(worker);
	}
#else
	PINF_2("Notifying manager.");
	mgr->workerFinished(worker);
#endif /* DISABLE_D2MCE */
}

/**
 * Get the number of runners.
 */
unsigned Master::numberOfRunners()
{
	_d->rsocksmx.lock();
	unsigned n = _d->rsocks.size();
	_d->rsocksmx.unlock();
	return n;
}

}
