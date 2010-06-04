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
	RunnerConnectionListener listener(&_msock, master_port, &_runnersocks, timeout);
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

	_state = READY;
	return true;
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
 * Send an worker actor to runners to execute.
 */
void Master::sendActor(AbstractWorkerActor *actor, ManagerActor *owner)
{
//	TLVCommand msg;
//	msg.setCommand(TLVCommand::ACTOR_RUN);
//	msg.setParameter(actor);
//
//	// Send to given runner.
//	if (rsock) {
//		TLVReaderWriter rw(rsock);
//		return rw.write(msg);
//	}
//
//	// Send to all runners.
//	bool success = true;
//	for (unsigned i = 0; i < _runnersocks.size(); i++) {
//		TLVReaderWriter rw(_runnersocks[i]);
//		success &= rw.write(msg);
//	}
//	return success;
}

}
