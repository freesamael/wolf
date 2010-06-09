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
#include <map>
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

	inline State state() const { return _state; } ///< Get the state of the agent.
	inline const std::vector<cml::TCPSocket *>& runners() const
			{ return _runnersocks; } ///< Get the sockets of runners.

	bool setup(uint16_t runner_port, uint16_t master_port, const
			std::string &appname, unsigned int timeout = 2);
	void runWorker(AbstractWorkerActor *worker, ManagerActor *mgr);
	void shutdown();
	void runnerConnected(cml::TCPSocket *runnersock);
	void workerFinished(uint32_t wseq, AbstractWorkerActor *worker);

private:
	Master(): SINGLETON_MEMBER_INITLST,
		_state(NOT_READY), _msock(), _runnersocks(), _mgrqueue() {}
	State _state;
	cml::TCPSocket _msock;
	std::vector<cml::TCPSocket *> _runnersocks;
	std::map<uint32_t, ManagerActor *> _mgrqueue;
};

}

#endif /* MASTER_H_ */
