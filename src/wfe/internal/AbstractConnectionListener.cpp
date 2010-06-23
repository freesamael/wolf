/**
 * \file AbstractConnectionListener.cpp
 * \date Jun 14, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "TLVReaderWriter.h"
#include "TLVCommand.h"
#include "AbstractConnectionListener.h"

using namespace cml;

namespace wfe
{

AbstractConnectionListener::AbstractConnectionListener(TCPSocket *lsock,
		uint16_t lport): _lsock(lsock), _listener(_lsock),
		_listhread(&_listener)
{
	_lsock->passiveOpen(lport);
	_listener.attach(this);
}

/**
 * Start listener.
 */
void AbstractConnectionListener::start()
{
	PINF_2("Start listening.");
	_listhread.start();
}

/**
 * Set the end condition of listener and wait until it ends.
 */
void AbstractConnectionListener::stop()
{
	PINF_2("Stop listening.");
	_listener.setDone();
	_listhread.join();
}

void AbstractConnectionListener::update(AbstractObservable *o)
{
	// Check observable.
	TCPConnectionListener *ca;
	if (!(ca = dynamic_cast<TCPConnectionListener*>(o))) {
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
	TLVCommand *msg;
	if (!(msg = dynamic_cast<TLVCommand *>(tcprw.read()))) {
		PERR("Invalid incoming message.");
	} else if (msg->command() != TLVCommand::HELLO_RUNNER) {
		PERR("Expected command " <<
				TLVCommand::CommandString[TLVCommand::HELLO_RUNNER] <<
				"but got " <<
				TLVCommand::CommandString[msg->command()] << ".");
	} else {
		PINF_2("Got an incoming runner connection.");
		// Check nonblocking flag and set to block if needed.
		// I noticed that the default value might be nonblocking on BSD/Mac.
		if (sock->isNonblock())
			sock->setNonblock(false);
		notify(sock);
	}
	delete msg;
}

}
