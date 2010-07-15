/**
 * \file AConnectionListener.cpp
 * \date Jun 14, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "CTlvReaderWriter.h"
#include "CTcpTlvReaderWriter.h"
#include "CTlvCommand.h"
#include "AConnectionListener.h"

using namespace cml;

namespace wfe
{

AConnectionListener::AConnectionListener(CTcpSocket *lsock,
		in_port_t lport): _lsock(lsock), _listener(_lsock),
		_listhread(&_listener)
{
	_lsock->passiveOpen(lport);
	_listener.attach(this);
}

/**
 * Start listener.
 */
void AConnectionListener::start()
{
	PINF_2("Start listening.");
	_listhread.start();
}

/**
 * Set the end condition of listener and wait until it ends.
 */
void AConnectionListener::stop()
{
	PINF_2("Stop listening.");
	_listener.setDone();
	_listhread.join();
}

void AConnectionListener::update(AObservable *o)
{
	// Check observable.
	CTcpConnectionListener *ca;
	if (!(ca = dynamic_cast<CTcpConnectionListener*>(o))) {
		PERR("Invalid update call from a object that is not TCPConnectionAcceptor.");
		return;
	}

	// Check socket.
	CTcpSocket *sock;
	if (!(sock = ca->lastAcceptedSocket())) {
		PERR("No socket object found.");
		return;
	}

	// Check message.
	CTlvReaderWriter tcprw(sock);
	CTlvCommand *msg;
	if (!(msg = dynamic_cast<CTlvCommand *>(tcprw.read()))) {
		PERR("Invalid incoming message.");
	} else if (msg->command() != CTlvCommand::HELLO_RUNNER) {
		PERR("Expected command " <<
				CTlvCommand::CommandString[CTlvCommand::HELLO_RUNNER] <<
				"but got " <<
				CTlvCommand::CommandString[msg->command()] << ".");
	} else {
		PINF_2("Got an incoming runner connection.");
		// Check nonblocking flag and set to block if needed.
		// I noticed that the default value might be nonblocking on BSD/Mac.
		if (!sock->blockable())
			sock->setBlockable(true);
		notify(sock);
	}
	delete msg;
}

}
