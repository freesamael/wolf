/**
 * \file AConnectionListener.h
 * \date Jun 14, 2010
 * \author samael
 */

#ifndef ACONNECTIONLISTENER_H_
#define ACONNECTIONLISTENER_H_

#include <inttypes.h>
#include "CThread.h"
#include "CTcpSocket.h"
#include "HelperMacros.h"
#include "AObservable.h"
#include "CTcpConnectionListener.h"

namespace wfe
{

/**
 * Used to listen incoming runner connections.
 */
class AConnectionListener: public cml::IObserver
{
public:
	AConnectionListener(cml::CTcpSocket *lsock, in_port_t lport);
	virtual ~AConnectionListener() {}
	void start();
	void stop();
	void update(cml::AObservable *o);
	virtual void notify(cml::CTcpSocket *sock) = 0;

private:
	AConnectionListener(const AConnectionListener &UNUSED(o)):
		cml::IObserver(), _lsock(NULL), _listener(NULL),
		_listhread(&_listener) {}
	AConnectionListener& operator=(const AConnectionListener
			&UNUSED(o)) { return *this; }
	cml::CTcpSocket *_lsock;
	cml::CTcpConnectionListener _listener;
	cml::CThread _listhread;
};

}

#endif /* ACONNECTIONLISTENER_H_ */
