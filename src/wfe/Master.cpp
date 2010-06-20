/**
 * \file Master.cpp
 * \date Apr 1, 2010
 * \author samael
 */

#include <sys/time.h>
#include <unistd.h>
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
	PData(): cmdsdr(), rsocks(), clis(), clthreads(),
			mgrq() {}
	MasterSideCommandSender cmdsdr;
	std::vector<cml::TCPSocket *> rsocks;
	std::vector<MasterSideCommandListener *> clis;
	std::vector<cml::Thread *> clthreads;
	std::map<uint32_t, ManagerActor *> mgrq;
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
	_d->cmdsdr.hello(runner_port);

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
	for (unsigned i = 0; i < _d->rsocks.size(); i++) {
		uint32_t seq = _d->cmdsdr.runWorker(_d->rsocks[i], worker);
		_d->mgrq[seq] = mgr;
	}
#else
	TCPSocket *runner = dispatcher()->choose(_d->rsocks);
	if (runner) {
		uint32_t seq = _d->cmdsdr.runWorker(runner, worker);
		_d->mgrq[seq] = mgr;
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
	for (unsigned i = 0; i < _d->rsocks.size(); i++) {
		addrs.push_back(_d->rsocks[i]->peerAddress());
	}
	_d->cmdsdr.addRunner(runnersock, addrs);
	_d->rsocks.push_back(runnersock);
}

/**
 * Notify Master that a worker has finished.
 */
void Master::workerFinished(uint32_t wseq, const AbstractWorkerActor &worker)
{
	PINF_2("Worker " << wseq << " finished.");

	// Find the belonging manager.
	map<uint32_t, ManagerActor *>::iterator iter;
	if ((iter = _d->mgrq.find(wseq)) == _d->mgrq.end()) {
		PERR("No manager found owning worker with sequence = " << wseq);
		return;
	}

	// Take the value and remove the manager from the queue.
	ManagerActor *mgr = iter->second;
	_d->mgrq.erase(iter);

#ifndef DISABLE_D2MCE
	// Check if it's the last worker owned by that manager.
	map<uint32_t, ManagerActor *>::iterator tmpiter;
	bool lastone = true;
	for (tmpiter = _d->mgrq.begin();
			tmpiter != _d->mgrq.end(); tmpiter++) {
		if (tmpiter->second == mgr) {
			lastone = false;
			break;
		}
	}

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
unsigned Master::numberOfRunners() const
{
	return _d->rsocks.size();
}

}
