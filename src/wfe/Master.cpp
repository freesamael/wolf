/**
 * \file Master.cpp
 * \date Apr 1, 2010
 * \author samael
 */

#include <sys/time.h>
#include <unistd.h>
#include <UDPSocket.h>
#include <TLVReaderWriter.h>
#include <Thread.h>
#include <SingletonAutoDestructor.h>
#include <TLVUInt32.h>
#include "D2MCE.h"
#include "Master.h"
#include "TLVMessage.h"
#include "internal/RunnerConnectionListener.h"

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

	// Listen and wait for join message.
	RunnerConnectionListener listener(&_msock, master_port, &_runnersocks, timeout);
	listener.start();
	// Join d2mce and broadcast notification.
	joinGroup(appname);
	broadcastHelloMessage(runner_port);

	// Check the runners.
	listener.stop();
	if (_runnersocks.size() == 0) {
		PERR("No runner found.");
		return false;
	}

	// Ask runners to connect each other.
	for (unsigned i = 0; i < _runnersocks.size(); i++) {
		TLVReaderWriter rw(_runnersocks[i]);
		for (unsigned j = 0; i < i; j++) {
			TLVUInt32 addr((uint32_t)_runnersocks[j]->peerAddress().toInetAddr());
			TLVMessage msg(TLVMessage::RUNNER_ADD, &addr);
			rw.write(msg);
		}
		TLVMessage startmsg(TLVMessage::RUNNER_START);
		rw.write(startmsg);
	}

	_state = READY;
	return true;
}

/**
 * Tell the runners to shutdown. It should be perform before program exits.
 */
bool Master::shutdown()
{
	if (_state != READY)
		return false;

	// Construct command.
	TLVMessage msg;

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
bool Master::sendActor(AbstractWorkerActor *actor, TCPSocket *rsock)
{
	if (_state != READY)
		return false;

	TLVMessage msg;
	msg.setCommand(TLVMessage::ACTOR_RUN);
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
 * \internal
 * Join the D2MCE computing group.
 */
void Master::joinGroup(const string &appname)
{
#ifndef DISABLE_D2MCE
	// Join D2MCE computing group.
	D2MCE::instance()->join(appname);
	PINFO(D2MCE::instance()->getNumberOfNodes() <<
			" nodes inside the group, node id = " <<
			D2MCE::instance()->nodeId() << ".");
#endif /* DISABLE_D2MCE */
}

/**
 * Send hello message.
 */
void Master::broadcastHelloMessage(uint16_t runner_port)
{
	UDPSocket usock;
	TLVReaderWriter udprw(&usock);
	usock.setBroadcast(true);
	usock.setTTL(1);
	udprw.sendto(TLVMessage(TLVMessage::HELLO_MASTER),
			HostAddress::BroadcastAddress, runner_port);
}

}
