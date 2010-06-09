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
#include "internal/RunnerConnectionListener.h"
#include "internal/MasterCommandSender.h"

using namespace std;
using namespace cml;

namespace wfe
{

SINGLETON_REGISTRATION(Master);
SINGLETON_DEPENDS_SOCKET(Master);
SINGLETON_REGISTRATION_END();

const string Master::StateString[] = { "Not Ready", "Ready" };

/**
 * Setup the master. It must be called before other operations.
 */
bool Master::setup(uint16_t runner_port, uint16_t master_port,
		const string &appname, unsigned int timeout)
{
	if (_state != NOT_READY)
		return false;

	// Start waiting runner connections, join d2mce and broadcast hello msg.
	MasterCommandSender cmdr;
	RunnerConnectionListener listener(this, &_msock, master_port, timeout);
	listener.start();
	cmdr.joinD2MCE(appname);
	cmdr.hello(runner_port);

	// Check the runners.
	listener.stop();
	if (_runnersocks.size() == 0) {
		PERR("No runner found.");
		return false;
	}

	// Start all runners.
	for (unsigned i = 0; i < _runnersocks.size(); i++) {
		cmdr.startRunner(_runnersocks[i]);
	}

	_state = READY;
	return true;
}

/**
 * Send a worker out to run.
 */
void Master::runWorker(AbstractWorkerActor *worker, ManagerActor *mgr)
{
	MasterCommandSender cmdr;
#ifndef DISABLE_D2MCE
	for (unsigned i = 0; i < _runnersocks.size(); i++) {
		_mgrqueue[cmdr.runWorker(_runnersocks[i], worker)] = mgr;
	}
#endif
}

/**
 * Tell the runners to shutdown. It should be perform before program exits.
 */
void Master::shutdown()
{
	// Shutdown all runners.
	MasterCommandSender cmdr;
	for (unsigned i = 0; i < _runnersocks.size(); i++) {
		cmdr.shutdown(_runnersocks[i]);
	}
	_state = NOT_READY;
}

/**
 * Used by RunnerCommandListener to notify that a runner is got.
 */
void Master::runnerConnected(cml::TCPSocket *runnersock)
{
	MasterCommandSender cmdr;
	vector<HostAddress> addrs;
	for (unsigned i = 0; i < _runnersocks.size(); i++) {
		addrs.push_back(_runnersocks[i]->peerAddress());
	}
	cmdr.addRunner(runnersock, addrs);
	_runnersocks.push_back(runnersock);
}

/**
 * Notify Master that a worker has finished.
 */
void Master::workerFinished(uint32_t wseq, AbstractWorkerActor *worker)
{
	map<uint32_t, ManagerActor *>::iterator iter;
	if ((iter = _mgrqueue.find(wseq)) == _mgrqueue.end()) {
		PERR("No manager found owning worker with sequence = " << wseq);
		return;
	}

#ifndef DISABLE_D2MCE
	// Check if it's the last worker owned by that manager.
	map<uint32_t, ManagerActor *>::iterator tmpiter;
	bool lastone = true;
	for (tmpiter = _mgrqueue.begin(); tmpiter != _mgrqueue.end(); tmpiter++) {
		if (tmpiter->second == iter->second) {
			lastone = false;
			break;
		}
	}

	// Notify manager only if it's the last worker.
	if (lastone)
		iter->second->workerFinished();
#else
	iter->second->workerFinished();
#endif
	_mgrqueue.erase(iter);
}

}
