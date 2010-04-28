/**
 * \file RunnerConnectionListener.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include <iostream>
#include <TCPConnectionListener.h>
#include <TLVReaderWriter.h>
#include <Thread.h>
#include "RunnerConnectionListener.h"
#include "TLVMessage.h"

using namespace std;
using namespace cml;

namespace wfe
{

RunnerConnectionListener::RunnerConnectionListener(TCPSocket *msock,
		uint16_t master_port, vector<TCPSocket *> *runnersocks,
		unsigned timeout):
				_msock(msock), _runnersocks(runnersocks), _timeout(timeout),
				_listener(_msock), _listhread(&_listener)
{
	msock->passiveOpen(master_port);
}

/**
 * Assignment.
 */
RunnerConnectionListener& RunnerConnectionListener::operator=(const RunnerConnectionListener &o)
{
	_msock = o._msock;
	_runnersocks = o._runnersocks;
	_timeout = o._timeout;
	_listener = o._listener;
	_listhread = o._listhread;
	return *this;
}

/**
 * Start acceptor.
 */
void RunnerConnectionListener::start()
{
	_listhread.start();
}

/**
 * Wait timeout seconds and stop acceptor.
 */
bool RunnerConnectionListener::join()
{
	sleep(_timeout);
	_listener.setDone();
	return _listhread.join();
}

/**
 * Used to process the events from TCPConnectionAcceptor.
 */
void RunnerConnectionListener::update(AbstractObservable *o)
{
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