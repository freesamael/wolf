/**
 * \file TCPConnectionListener.h
 * \date Apr 27, 2010
 * \author samael
 */

#ifndef TCPCONNECTIONLISENTER_H_
#define TCPCONNECTIONLISENTER_H_

#include <TCPSocket.h>
#include "AbstractObservable.h"
#include "IRunnable.h"
#include "Mutex.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * A listener that continuously accept incoming connections on given
 * server socket until setDown() is called. It notifies all observers each
 * time a new connection is accepted, and clients can use lastAcceptedSocket()
 * to get the last socket accepted.
 */
class TCPConnectionListener: public AbstractObservable, public IRunnable
{
public:
	TCPConnectionListener(TCPSocket *server):
		_mutex(), _done(false), _server(server), _ssock(NULL) {}

	inline TCPSocket* lastAcceptedSocket() { return _ssock; }
	inline bool isDone() const { return _done; }
	inline void setDone(bool d = true) { _done = d; }
	inline bool mutexLock() { return _mutex.lock(); }
	inline bool mutexUnlock() { return _mutex.unlock(); }
	void run();

private:
	TCPConnectionListener(const TCPConnectionListener &UNUSED(o)):
		AbstractObservable(), _mutex(), _done(false), _server(NULL),
		_ssock(NULL) {}
	TCPConnectionListener& operator=(const TCPConnectionListener &UNUSED(o))
		{ return *this; }
	Mutex _mutex;
	bool _done;
	TCPSocket *_server;
	TCPSocket *_ssock;
};

}

#endif /* TCPCONNECTIONLISENTER_H_ */
