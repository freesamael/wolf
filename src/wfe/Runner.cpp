/**
 * \file Runner.cpp
 * \date Apr 1, 2010
 * \author samael
 */

#include <iostream>
#include <string>
#include <deque>
#include "Thread.h"
#include "UDPSocket.h"
#include "TLVReaderWriter.h"
#include "HelperMacros.h"
#include "Runner.h"
#include "D2MCE.h"
#include "Mutex.h"
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
	RunnerSideConnectionListener *pcnlis;
	RunnerSideCommandListener *pmclis;
	vector<TCPSocket *> rsocks;
	vector<RunnerSideCommandListener *> rclis;
	vector<Thread *> rclthreads;
	RunnerSideCommandSender cmdsdr;
	deque<pair<uint32_t, AbstractWorkerActor *> > wq;
	Mutex wqmx;
};

Runner::Runner(uint16_t master_port, uint16_t runner_port,
		const string &appname): _mport(master_port), _rport(runner_port),
		_appname(appname), _msock(NULL), _rsock(), _d(new PData())
{

}

Runner::~Runner()
{
	delete _d;
}

void Runner::run()
{
	// Connect to master and join D2MCE.
	RunnerSideMasterConnector msconn;
	if (!(_msock = msconn.connect(_mport, _rport))) {
		PERR("Runner fails. Exit.");
		return;
	}
	_d->cmdsdr.joinD2MCE(_appname);

	// Start listening connections from other runners.
	_d->pcnlis = new RunnerSideConnectionListener(this, &_rsock, _rport);
	_d->pcnlis->start();

	// Start listening master commands.
	_d->pmclis = new RunnerSideCommandListener(this, _msock);
	Thread cmdthread(_d->pmclis);
	cmdthread.start();

	// Send hello message to master.
	_d->cmdsdr.hello(_msock);

	// Block wait until command processing loop ends.
	cmdthread.join();
}


/**
 * Add a worker into the waiting queue for execution.
 */
void Runner::putWorker(uint32_t wseq, AbstractWorkerActor *worker)
{
	_d->wqmx.lock();
	_d->wq.push_back(pair<uint32_t, AbstractWorkerActor *>(wseq, worker));
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

	return w;
}

/**
 * Notify that a worker has been finished.
 */
void Runner::workerFinished(uint32_t wseq, AbstractWorkerActor *worker)
{
	_d->cmdsdr.workerFinished(_msock, wseq, worker);
	delete worker;
}

/**
 * Called when a runner connection got.
 */
void Runner::runnerConnected(TCPSocket *runnersock)
{
	RunnerSideCommandListener *lis =
			new RunnerSideCommandListener(this, runnersock);
	Thread *listhread = new Thread(lis);
	listhread->start();

	_d->rsocks.push_back(runnersock);
	_d->rclis.push_back(lis);
	_d->rclthreads.push_back(listhread);
}

}
