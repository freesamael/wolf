/**
 * \file RunnerConnectionAcceptor.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef RUNNERCONNECTIONACCEPTOR_H_
#define RUNNERCONNECTIONACCEPTOR_H_

#include <vector>
#include <IObserver.h>
#include <AbstractObservable.h>
#include <TCPSocket.h>
#include <TCPConnectionAcceptor.h>
#include <Thread.h>
#include <HelperMacros.h>

namespace wfe
{

/**
 * The proxy between TCPConnectionAcceptor and Master. Remember that the master
 * socket should be passively opened before start the acceptor.
 */
class RunnerConnectionAcceptor: public cml::IObserver
{
public:
	RunnerConnectionAcceptor(cml::TCPSocket *msock,
			std::vector<cml::TCPSocket *> *runnersocks, unsigned timeout):
				_msock(msock), _runnersocks(runnersocks),
				_timeout(timeout), _acptor(_msock), _acpthread(&_acptor) {}
	RunnerConnectionAcceptor(const RunnerConnectionAcceptor &o):
		_msock(o._msock), _runnersocks(o._runnersocks),
		_timeout(o._timeout), _acptor(_msock), _acpthread(&_acptor) {}
	RunnerConnectionAcceptor& operator=(const RunnerConnectionAcceptor &o);

	void start();
	bool join();
	void update(cml::AbstractObservable *o);

private:
	cml::TCPSocket *_msock;
	std::vector<cml::TCPSocket *> *_runnersocks;
	unsigned _timeout;
	cml::TCPConnectionAcceptor _acptor;
	cml::Thread _acpthread;
};

}

#endif /* RUNNERCONNECTIONACCEPTOR_H_ */
