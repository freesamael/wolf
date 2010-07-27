/**
 * \file AConnectionListener.h
 * \date Jun 14, 2010
 * \author samael
 */

#ifndef ACONNECTIONLISTENER_H_
#define ACONNECTIONLISTENER_H_

#include <inttypes.h>
#include "CThread.h"
#include "CTcpServer.h"
#include "CTcpSocket.h"
#include "HelperMacros.h"
#include "AObservable.h"
#include "CTcpConnectionListener.h"

namespace wolf
{

/**
 * Used to listen incoming runner connections.
 */
class AConnectionListener: public wolf::IObserver
{
public:
	AConnectionListener(wolf::CTcpServer *server, in_port_t lport);
	virtual ~AConnectionListener() {}
	void start();
	void stop();
	void update(wolf::AObservable *o);
	virtual void notify(wolf::CTcpSocket *sock) = 0;

private:
	AConnectionListener(const AConnectionListener &UNUSED(o)):
		wolf::IObserver(), _server(NULL), _listener(NULL),
		_listhread(&_listener) {}
	AConnectionListener& operator=(const AConnectionListener
			&UNUSED(o)) { return *this; }
	wolf::CTcpServer *_server;
	wolf::CTcpConnectionListener _listener;
	wolf::CThread _listhread;
};

}

#endif /* ACONNECTIONLISTENER_H_ */
