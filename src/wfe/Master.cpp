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
	PData(): CommandSender(), RunnerSocks(), CommandListeners(), CLThreads(),
			ManagerWaitingQueue() {}
	MasterSideCommandSender CommandSender;
	std::vector<cml::TCPSocket *> RunnerSocks;
	std::vector<MasterSideCommandListener *> CommandListeners;
	std::vector<cml::Thread *> CLThreads;
	std::map<uint32_t, ManagerActor *> ManagerWaitingQueue;
};

SINGLETON_REGISTRATION(Master);
SINGLETON_DEPENDS_SOCKET(Master);
SINGLETON_REGISTRATION_END();

const string Master::StateString[] = { "Not Ready", "Ready", "End" };

Master::Master():
		SINGLETON_MEMBER_INITLST,	_state(NOT_READY), _msock(), _defdisp(),
		_activedisp(&_defdisp), _data(new PData)
{
}

Master::~Master()
{
	for (unsigned i = 0; i < _data->CommandListeners.size(); i++)
		delete _data->CommandListeners[i];
	for (unsigned i = 0; i < _data->CLThreads.size(); i++)
		delete _data->CLThreads[i];
	delete _data;
}

/**
 * Setup the master. It must be called before other operations.
 */
bool Master::setup(uint16_t runner_port, uint16_t master_port,
		const string &appname, unsigned int timeout)
{
	if (_state != NOT_READY)
		return false;

	// Start waiting runner connections.
	MasterSideConnectionListener listener(this, &_msock, master_port, timeout);
	listener.start();

	// Join D2MCE group and broadcast hello message.
	_data->CommandSender.joinD2MCE(appname);
	_data->CommandSender.hello(runner_port);

	// Check the runners.
	listener.stop();
	if (_data->RunnerSocks.size() == 0) {
		PERR("No runner found.");
		return false;
	}

	// Bind command listeners to each runner, and start all runners.
	for (unsigned i = 0; i < _data->RunnerSocks.size(); i++) {
		MasterSideCommandListener *cl =
				new MasterSideCommandListener(this, _data->RunnerSocks[i]);
		Thread *clth = new Thread(cl);
		clth->start();
		_data->CommandListeners.push_back(cl);
		_data->CLThreads.push_back(clth);
		_data->CommandSender.startRunner(_data->RunnerSocks[i]);
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
	for (unsigned i = 0; i < _data->RunnerSocks.size(); i++) {
		uint32_t seq = _data->CommandSender.runWorker(_data->RunnerSocks[i],
				worker);
		_data->ManagerWaitingQueue[seq] = mgr;
	}
#else
	TCPSocket *runner = dispatcher()->choose(_data->RunnerSocks);
	if (runner) {
		uint32_t seq = _data->CommandSender.runWorker(runner, worker);
		_data->ManagerWaitingQueue[seq] = mgr;
	}
#endif /* DISABLE_D2MCE */
}

/**
 * Tell the runners to shutdown. It should be perform before program exits.
 */
void Master::shutdown()
{
	// Shutdown all runners and stop all command listeners.
	for (unsigned i = 0; i < _data->RunnerSocks.size(); i++) {
		_data->CommandSender.shutdown(_data->RunnerSocks[i]);
		_data->CommandListeners[i]->setDone();
	}

	// Wait listener threads end.
	for (unsigned i = 0; i < _data->CLThreads.size(); i++)
		_data->CLThreads[i]->join();

	_state = END;
}

/**
 * Used by RunnerCommandListener to notify that a runner is got.
 */
void Master::runnerConnected(cml::TCPSocket *runnersock)
{
	PINFO_2("Got one runner.");
	vector<HostAddress> addrs;
	for (unsigned i = 0; i < _data->RunnerSocks.size(); i++) {
		addrs.push_back(_data->RunnerSocks[i]->peerAddress());
	}
	_data->CommandSender.addRunner(runnersock, addrs);
	_data->RunnerSocks.push_back(runnersock);
}

/**
 * Notify Master that a worker has finished.
 */
void Master::workerFinished(uint32_t wseq, const AbstractWorkerActor &worker)
{
	PINFO_2("Worker " << wseq << " finished.");
	map<uint32_t, ManagerActor *>::iterator iter;
	if ((iter = _data->ManagerWaitingQueue.find(wseq)) ==
			_data->ManagerWaitingQueue.end()) {
		PERR("No manager found owning worker with sequence = " << wseq);
		return;
	}

#ifndef DISABLE_D2MCE
	// Check if it's the last worker owned by that manager.
	map<uint32_t, ManagerActor *>::iterator tmpiter;
	bool lastone = true;
	for (tmpiter = _data->ManagerWaitingQueue.begin();
			tmpiter != _data->ManagerWaitingQueue.end(); tmpiter++) {
		if (tmpiter->second == iter->second) {
			lastone = false;
			break;
		}
	}

	// Notify manager only if it's the last worker.
	if (lastone)
		iter->second->workerFinished(worker);
#else
	iter->second->workerFinished(worker);
#endif /* DISABLE_D2MCE */
	_data->ManagerWaitingQueue.erase(iter);
}

/**
 * Get the number of runners.
 */
unsigned Master::numberOfRunners() const
{
	return _data->RunnerSocks.size();
}

}
