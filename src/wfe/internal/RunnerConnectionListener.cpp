/**
 * \file RunnerConnectionListener.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include <iostream>
#include <vector>
#include "TCPConnectionListener.h"
#include "TLVReaderWriter.h"
#include "Thread.h"
#include "RunnerConnectionListener.h"
#include "TLVCommand.h"
#include "MasterCommandSender.h"

using namespace std;
using namespace cml;

namespace wfe
{

RunnerConnectionListener::RunnerConnectionListener(TCPSocket *msock,
		uint16_t listen_port, vector<TCPSocket *> *runnersocks,
		unsigned timeout):
				_msock(msock), _runnersocks(runnersocks), _timeout(timeout),
				_listener(_msock), _listhread(&_listener)
{
	msock->passiveOpen(listen_port);
	_listener.attach(this);
}

RunnerConnectionListener::RunnerConnectionListener(const RunnerConnectionListener &o):
		_msock(o._msock), _runnersocks(o._runnersocks),
		_timeout(o._timeout), _listener(_msock), _listhread(&_listener)
{
	_listener.attach(this);
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
	_listener.attach(this);
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
bool RunnerConnectionListener::stop()
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
		// Ask runner to add all other runners, and add the runner into local
		// runner list.
		MasterCommandSender cmdr;
		vector<HostAddress> addrs
		PINFO("Got one runner.");
		for (unsigned i = 0; i < _runnersocks->size(); i++) {
			addrs.push_back((*_runnersocks)[i]->peerAddress());
		}
		cmdr.addRunner(sock, addrs);
		_runnersocks->push_back(sock);
	}
	delete msg;
}

}
