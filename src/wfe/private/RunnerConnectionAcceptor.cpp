/**
 * \file RunnerConnectionAcceptor.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include <iostream>
#include <TCPConnectionAcceptor.h>
#include <TLVReaderWriter.h>
#include <Thread.h>
#include "RunnerConnectionAcceptor.h"
#include "TLVMessage.h"

using namespace std;
using namespace cml;

namespace wfe
{

/**
 * Assignment.
 */
RunnerConnectionAcceptor& RunnerConnectionAcceptor::operator=(const RunnerConnectionAcceptor &o)
{
	_msock = o._msock;
	_runnersocks = o._runnersocks;
	_timeout = o._timeout;
	_acptor = o._acptor;
	_acpthread = o._acpthread;
	return *this;
}

/**
 * Start acceptor.
 */
void RunnerConnectionAcceptor::start()
{
	_acpthread.start();
}

/**
 * Wait timeout seconds and stop acceptor.
 */
bool RunnerConnectionAcceptor::join()
{
	sleep(_timeout);
	_acptor.setDone();
	return _acpthread.join();
}

/**
 * Used to process the events from TCPConnectionAcceptor.
 */
void RunnerConnectionAcceptor::update(AbstractObservable *o)
{
	// Check observable.
	TCPConnectionAcceptor *ca;
	if (!(ca = dynamic_cast<TCPConnectionAcceptor*>(o))) {
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
		_runnersocks->push_back(sock);
	}
	delete msg;
}

}
