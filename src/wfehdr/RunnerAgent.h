/**
 * \file RunnerAgent.h
 * \date Apr 1, 2010
 * \author samael
 */

#ifndef RUNNERAGENT_H_
#define RUNNERAGENT_H_

#include <iostream>
#include <vector>
#include <string>
#include <TCPSocket.h>
#include <HelperMacros.h>
#include <IObserver.h>
#include <AbstractObservable.h>
#include "AbstractWorkerActor.h"

namespace wfe
{

class RunnerAgent: public cml::IObserver
{
	SINGLETON(RunnerAgent);
public:
	typedef enum State {
		NOT_READY,
		READY
	} State;
	static const char *StateString[];
	bool setup(uint16_t runner_port, uint16_t master_port, const
			std::string &appname, unsigned int timeout = 2);
	bool shutdown();
	bool sendActor(AbstractWorkerActor *actor, cml::TCPSocket *rsock = NULL);
	void update(cml::AbstractObservable *o);

	/// Get the state of the agent.
	inline State state() const { return _state; }
	/// Get the sockets of runners.
	inline const std::vector<cml::TCPSocket *>& runners() const
			{ return _runnersocks; }

private:
	RunnerAgent(): SINGLETON_MEMBER_INITLST,
		_state(NOT_READY), _msock(), _runnersocks() {}
	State _state;
	cml::TCPSocket _msock;
	std::vector<cml::TCPSocket *> _runnersocks;
};

}

#endif /* RUNNERAGENT_H_ */
