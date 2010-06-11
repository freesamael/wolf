/**
 * \file MasterSideConnectionListener.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef MASTERSIDECONNECTIONLISTENER_H_
#define MASTERSIDECONNECTIONLISTENER_H_

#include <vector>
#include "IObserver.h"
#include "AbstractObservable.h"
#include "TCPSocket.h"
#include "TCPConnectionListener.h"
#include "Thread.h"
#include "HelperMacros.h"
#include "Master.h"

namespace wfe
{

/**
 * The proxy between TCPConnectionListener and Master.
 */
class MasterSideConnectionListener: public cml::IObserver
{
public:
	MasterSideConnectionListener(Master *master, cml::TCPSocket *msock,
			uint16_t listen_port);

	void start();
	void stop();
	void update(cml::AbstractObservable *o);

private:
	MasterSideConnectionListener(const MasterSideConnectionListener &UNUSED(o)):
		_master(NULL), _msock(NULL), _listener(NULL), _listhread(&_listener) {}
	MasterSideConnectionListener& operator=(const MasterSideConnectionListener &UNUSED(o))
		{ return *this; }
	Master *_master;
	cml::TCPSocket *_msock;
	cml::TCPConnectionListener _listener;
	cml::Thread _listhread;
};

}

#endif /* MASTERSIDECONNECTIONLISTENER_H_ */
