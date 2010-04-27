/**
 * \file RunnerAgent.cpp
 * \date Apr 1, 2010
 * \author samael
 */

#include <sys/time.h>
#include <unistd.h>
#include <UDPSocket.h>
#include <TLVReaderWriter.h>
#include <Thread.h>
#include <SingletonAutoDestructor.h>
#include <TCPConnectionAcceptor.h>
#include "D2MCE.h"
#include "RunnerAgent.h"
#include "TLVMessage.h"

using namespace std;
using namespace cml;

namespace wfe
{

SINGLETON_REGISTRATION(RunnerAgent);
SINGLETON_DEPENDS_SOCKET(RunnerAgent);
SINGLETON_REGISTRATION_END();

const char *RunnerAgent::StateString[] = { "Not Ready", "Ready" };

/**
 * Setup the agent. It must be called before other agent operations.
 */
bool RunnerAgent::setup(uint16_t runner_port, uint16_t master_port,
		const string &appname, unsigned int timeout)
{
	if (_state != NOT_READY)
		return false;

	// Listen and wait for join message.
	TCPConnectionAcceptor acptor(&_msock);
	Thread athread(&acptor);
	_msock.passiveOpen(master_port);
	athread.start();

#ifndef DISABLE_D2MCE
	// Join D2MCE computing group.
	D2MCE::instance()->join(appname);
	PINFO(D2MCE::instance()->getNumberOfNodes() <<
			" nodes inside the group, node id = " <<
			D2MCE::instance()->nodeId() << ".");
#endif /* DISABLE_D2MCE */

	// Broadcast notification.
	UDPSocket usock;
	TLVReaderWriter udprw(&usock);
	usock.setBroadcast(true);
	usock.setTTL(1);
	udprw.sendto(TLVMessage(TLVMessage::HELLO_MASTER),
			HostAddress::BroadcastAddress, runner_port);

	// Wait until timed out.
	sleep(timeout);
	acptor.setDone();
	athread.join();

	if (_runnersocks.size() == 0) {
		PERR("No runner found.");
		return false;
	}


	_state = READY;
	return true;
}

/**
 * Tell the runners to shutdown. It should be perform before program exits.
 */
bool RunnerAgent::shutdown()
{
	if (_state != READY)
		return false;

	// Construct command.
	TLVMessage msg;	athread.setparam(&_msock, &_runnersocks);

	msg.setCommand(TLVMessage::SHUTDOWN);

	// Shutdown all runners.
	bool success = true;
	for (unsigned i = 0; i < _runnersocks.size(); i++) {
		TLVReaderWriter rw(_runnersocks[i]);
		success &= rw.write(msg);
	}
	_state = NOT_READY;
	return success;
}

/**
 * Send an worker actor to runners to execute.
 *
 * \param[in] actor
 * Actor to send.
 *
 * \param[in] rsock
 * Socket of runner to send actor to, or NULL for all runners.
 */
bool RunnerAgent::sendActor(AbstractWorkerActor *actor, TCPSocket *rsock)
{
	if (_state != READY)
		return false;

	TLVMessage msg;
	msg.setCommand(TLVMessage::RUN_ACTOR);
	msg.setParameter(actor);

	// Send to given runner.
	if (rsock) {
		TLVReaderWriter rw(rsock);
		return rw.write(msg);
	}

	// Send to all runners.
	bool success = true;
	for (unsigned i = 0; i < _runnersocks.size(); i++) {
		TLVReaderWriter rw(_runnersocks[i]);
		success &= rw.write(msg);
	}
	return success;
}

/**
 * Called by TCPConnectionAcceptor to accept an incoming runner connection.
 */
void RunnerAgent::update(AbstractObservable *o)
{
	// Check observable.
	TCPConnectionAcceptor *ca;
	if (!(ca = dynamic_cast<TCPConnectionAcceptor*>(o))) {
		PERR("Invalid update call from a object that is not TCPConnectionAcceptor.");
		return;
	}

	// Check socket.
	TCPSocket *sock;
	if (!(sock = ca->lastAcceptedSocket())) {
		PERR("No socket object found.");
		return;
	}

	// Check message.
	TLVReaderWriter tcprw(sock);
	TLVMessage *msg;
	if (!(msg = dynamic_cast<TLVMessage *>(tcprw.read()))) {
		PERR("Invalid incoming message.");
	} else if (msg->command() != TLVMessage::HELLO_SLAVE) {
		PERR("Expected command " <<
				TLVMessage::CommandString[TLVMessage::HELLO_SLAVE] <<
				"but got " <<
				TLVMessage::CommandString[msg->command()] << ".");
	} else {
		PINFO("Got one runner.");
		_runnersocks.push_back(sock);
	}
	delete msg;
}

}
