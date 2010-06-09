/**
 * \file RunnerConnectionListener.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef RUNNERCONNECTIONLISTENER_H_
#define RUNNERCONNECTIONLISTENER_H_

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
class RunnerConnectionListener: public cml::IObserver
{
public:
	RunnerConnectionListener(Master *master, cml::TCPSocket *msock,
			uint16_t listen_port, unsigned timeout);
	RunnerConnectionListener(const RunnerConnectionListener &o);
	RunnerConnectionListener& operator=(const RunnerConnectionListener &o);

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

#endif /* RUNNERCONNECTIONLISTENER_H_ */
