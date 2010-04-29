/**
 * \file RunnerConnectionListener.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef RUNNERCONNECTIONLISTENER_H_
#define RUNNERCONNECTIONLISTENER_H_

#include <vector>
#include <IObserver.h>
#include <AbstractObservable.h>
#include <TCPSocket.h>
#include <TCPConnectionListener.h>
#include <Thread.h>
#include <HelperMacros.h>

namespace wfe
{

/**
 * The proxy between TCPConnectionListener and Master.
 */
class RunnerConnectionListener: public cml::IObserver
{
public:
	RunnerConnectionListener(cml::TCPSocket *msock, uint16_t master_port,
			std::vector<cml::TCPSocket *> *runnersocks, unsigned timeout);
	RunnerConnectionListener(const RunnerConnectionListener &o);
	RunnerConnectionListener& operator=(const RunnerConnectionListener &o);

	void start();
	bool join();
	void update(cml::AbstractObservable *o);

private:
	cml::TCPSocket *_msock;
	std::vector<cml::TCPSocket *> *_runnersocks;
	unsigned _timeout;
	cml::TCPConnectionListener _listener;
	cml::Thread _listhread;
};

}

#endif /* RUNNERCONNECTIONLISTENER_H_ */
