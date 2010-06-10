/**
 * \file MasterSideConnectionListener.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include <iostream>
#include <vector>
#include "TCPConnectionListener.h"
#include "TLVReaderWriter.h"
#include "Thread.h"
#include "MasterSideConnectionListener.h"
#include "TLVCommand.h"

using namespace std;
using namespace cml;

namespace wfe
{

MasterSideConnectionListener::MasterSideConnectionListener(Master *master,
		TCPSocket *msock, uint16_t listen_port, unsigned timeout):
				_master(master), _msock(msock), _timeout(timeout),
				_listener(_msock), _listhread(&_listener)
{
	_msock->passiveOpen(listen_port);
	_listener.attach(this);
}

/**
 * Start acceptor.
 */
void MasterSideConnectionListener::start()
{
	_listhread.start();
}

/**
 * Wait timeout seconds and stop acceptor.
 */
void MasterSideConnectionListener::stop()
{
	sleep(_timeout);
	_listener.setDone();
	_listhread.join();
}

/**
 * Used to process the events from TCPConnectionAcceptor.
 */
void MasterSideConnectionListener::update(AbstractObservable *o)
{
	PINFO("Updating.");

	// Check observable.
	TCPConnectionListener *ca;
	if (!(ca = dynamic_cast<TCPConnectionListener*>(o))) {
		PERR("Invalid update call from a object that is not TCPConnectionAcceptor.");
		return;
	}

	// Check socket.
	ca->mutexLock();
	TCPSocket *sock = ca->lastAcceptedSocket();
	ca->mutexUnlock();
	if (!sock) {
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
		/// Notify master.
		_master->runnerConnected(sock);
	}
	delete msg;
}

}
