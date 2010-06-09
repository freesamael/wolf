/**
 * \file MasterSideRunnerConnectionListener.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef MASTERSIDERUNNERCONNECTIONLISTENER_H_
#define MASTERSIDERUNNERCONNECTIONLISTENER_H_

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
class MasterSideRunnerConnectionListener: public cml::IObserver
{
public:
	MasterSideRunnerConnectionListener(Master *master, cml::TCPSocket *msock,
			uint16_t listen_port, unsigned timeout);
	MasterSideRunnerConnectionListener(const MasterSideRunnerConnectionListener &o);
	MasterSideRunnerConnectionListener& operator=(const MasterSideRunnerConnectionListener &o);

	void start();
	bool stop();
	void update(cml::AbstractObservable *o);

private:
	Master *_master;
	cml::TCPSocket *_msock;
	unsigned _timeout;
	cml::TCPConnectionListener _listener;
	cml::Thread _listhread;
};

}

#endif /* MASTERSIDERUNNERCONNECTIONLISTENER_H_ */
