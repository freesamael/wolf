/**
 * \file TCPConnectionAcceptor.h
 * \date Apr 27, 2010
 * \author samael
 */

#ifndef TCPCONNECTIONACCEPTOR_H_
#define TCPCONNECTIONACCEPTOR_H_

#include <TCPSocket.h>
#include "AbstractObservable.h"
#include "IRunnable.h"
#include "Mutex.h"

namespace cml
{

/**
 * An acceptor that continuously accept incoming connections on given
 * server socket until setDown() is called. It notifies all observers each
 * time a new connection is accepted, and clients can use lastAcceptedSocket()
 * to get the last socket accepted.
 */
class TCPConnectionAcceptor: public AbstractObservable, public IRunnable
{
public:
	TCPConnectionAcceptor(TCPSocket *server):
		_mutex(), _done(false), _server(server), _ssock(NULL) {}
	/// Note that the mutex won't be the same on copy construction.
	TCPConnectionAcceptor(const TCPConnectionAcceptor &o):
		AbstractObservable(o), _mutex(), _done(o._done), _server(o._server),
		_ssock(o._ssock) {}
	TCPConnectionAcceptor& operator=(const TCPConnectionAcceptor &o);
	inline TCPSocket* lastAcceptedSocket() { return _ssock; }
	inline bool isDone() const { return _done; }
	inline void setDone() { _done = true; }
	inline bool mutexLock() { return _mutex.lock(); }
	inline bool mutexUnlock() { return _mutex.unlock(); }
	void run();

private:
	Mutex _mutex;
	bool _done;
	TCPSocket *_server;
	TCPSocket *_ssock;
};

}

#endif /* TCPCONNECTIONACCEPTOR_H_ */
