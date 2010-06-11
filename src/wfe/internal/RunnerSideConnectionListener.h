/**
 * \file RunnerSideConnectionListener.h
 * \date Jun 11, 2010
 * \author samael
 */

#ifndef RUNNERSIDECONNECTIONLISTENER_H_
#define RUNNERSIDECONNECTIONLISTENER_H_

#include "IObserver.h"
#include "Runner.h"
#include "TCPConnectionListener.h"
#include "Thread.h"

namespace wfe
{

class RunnerSideConnectionListener: public IObserver
{
public:
	RunnerSideConnectionListener(Runner *runner, cml::TCPSocket *sock,
			uint16_t port);
	void start();
	void stop();
	void update(cml::AbstractObservable *o);

private:
	cml::TCPConnectionListener _listener;
	cml::Thread _listhread;
};

}

#endif /* RUNNERSIDECONNECTIONLISTENER_H_ */
