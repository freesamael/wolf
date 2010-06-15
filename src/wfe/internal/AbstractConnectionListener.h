/**
 * \file AbstractConnectionListener.h
 * \date Jun 14, 2010
 * \author samael
 */

#ifndef ABSTRACTCONNECTIONLISTENER_H_
#define ABSTRACTCONNECTIONLISTENER_H_

#include <stdint.h>
#include "Thread.h"
#include "TCPSocket.h"
#include "HelperMacros.h"
#include "AbstractObservable.h"
#include "TCPConnectionListener.h"

namespace wfe
{

/**
 * Used to listen incoming runner connections.
 */
class AbstractConnectionListener: public cml::IObserver
{
public:
	AbstractConnectionListener(cml::TCPSocket *lsock, uint16_t lport);
	virtual ~AbstractConnectionListener() {}
	void start();
	void stop();
	void update(cml::AbstractObservable *o);
	virtual void notify(cml::TCPSocket *sock) = 0;

private:
	AbstractConnectionListener(const AbstractConnectionListener &UNUSED(o)):
		_lsock(NULL), _listener(NULL), _listhread(&_listener) {}
	AbstractConnectionListener& operator=(const AbstractConnectionListener
			&UNUSED(o)) { return *this; }
	cml::TCPSocket *_lsock;
	cml::TCPConnectionListener _listener;
	cml::Thread _listhread;
};

}

#endif /* ABSTRACTCONNECTIONLISTENER_H_ */
