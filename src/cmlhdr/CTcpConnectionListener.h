/**
 * \file CTcpConnectionListener.h
 * \date Apr 27, 2010
 * \author samael
 */

#ifndef CTCPCONNECTIONLISENTER_H_
#define CTCPCONNECTIONLISENTER_H_

#include "CTcpSocket.h"
#include "AObservable.h"
#include "IRunnable.h"
#include "CMutex.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * A listener that continuously accept incoming connections on given
 * server socket until setDown() is called. It notifies all observers each
 * time a new connection is accepted, and clients can use lastAcceptedSocket()
 * to get the last socket accepted.
 */
class CTcpConnectionListener: public AObservable, public IRunnable
{
public:
	CTcpConnectionListener(CTcpSocket *server):
		_mx(), _done(false), _server(server), _ssock(NULL) {}

	inline CTcpSocket* lastAcceptedSocket()
		{ _mx.lock(); CTcpSocket *s = _ssock; _mx.unlock(); return s; }
	inline bool isDone()
		{ _mx.lock(); bool d = _done; _mx.unlock(); return d; }
	inline void setDone(bool d = true)
		{ _mx.lock(); _done = d; _mx.unlock(); }
	void run();

private:
	CTcpConnectionListener(const CTcpConnectionListener &UNUSED(o)):
		AObservable(), IRunnable(), _mx(), _done(false), _server(NULL),
		_ssock(NULL) {}
	CTcpConnectionListener& operator=(const CTcpConnectionListener &UNUSED(o))
		{ return *this; }
	CMutex _mx;
	bool _done;
	CTcpSocket *_server;
	CTcpSocket *_ssock;
};

}

#endif /* CTCPCONNECTIONLISENTER_H_ */
