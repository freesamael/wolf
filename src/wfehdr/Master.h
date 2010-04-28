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
#include <TCPSocket.h>
#include <HelperMacros.h>
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
	static const char *StateString[];
	bool setup(uint16_t runner_port, uint16_t master_port, const
			std::string &appname, unsigned int timeout = 2);
	bool shutdown();
	bool sendActor(AbstractWorkerActor *actor, cml::TCPSocket *rsock = NULL);

	/// Get the state of the agent.
	inline State state() const { return _state; }
	/// Get the sockets of runners.
	inline const std::vector<cml::TCPSocket *>& runners() const
			{ return _runnersocks; }

private:
	// Private member functions.
	Master(): SINGLETON_MEMBER_INITLST,
		_state(NOT_READY), _msock(), _runnersocks() {}
	void joinGroup(const std::string &appname);
	void broadcastHelloMessage(uint16_t runner_port);
	// Private data members.
	State _state;
	cml::TCPSocket _msock;
	std::vector<cml::TCPSocket *> _runnersocks;
};

}

#endif /* MASTER_H_ */
