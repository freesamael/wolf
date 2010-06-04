/**
 * \file Master.h
 * \date Apr 1, 2010
 * \author samael
 */

#ifndef MASTER_H_
#define MASTER_H_

#include <iostream>
#include <vector>
#include <string>
#include "TCPSocket.h"
#include "HelperMacros.h"
#include "AbstractWorkerActor.h"

namespace wfe
{

/**
 * Master plays the middle man between runners and workflow executors.
 */
class Master
{
	SINGLETON(Master);
public:
	typedef enum State {
		NOT_READY,
		READY
	} State;
	static const std::string StateString[];
	bool setup(uint16_t runner_port, uint16_t master_port, const
			std::string &appname, unsigned int timeout = 2);
	void shutdown();
	void sendActor(AbstractWorkerActor *actor, ManagerActor *owner);

	/// Get the state of the agent.
	inline State state() const { return _state; }
	/// Get the sockets of runners.
	inline const std::vector<cml::TCPSocket *>& runners() const
			{ return _runnersocks; }

private:
	Master(): SINGLETON_MEMBER_INITLST,
		_state(NOT_READY), _msock(), _runnersocks() {}
	State _state;
	cml::TCPSocket _msock;
	std::vector<cml::TCPSocket *> _runnersocks;
};

}

#endif /* MASTER_H_ */
