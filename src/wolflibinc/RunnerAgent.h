/*
 * RunnerAgent.h
 *
 *  Created on: Apr 1, 2010
 *      Author: samael
 */

#ifndef RUNNERAGENT_H_
#define RUNNERAGENT_H_

#include <vector>
#include <pthread.h>
#include "TCPSocket.h"
#include "AbstractWorkerActor.h"

namespace wfe
{

class RunnerAgent
{
public:
	typedef enum State {
		NOT_READY,
		READY
	} State;
	static const char *StateString[];
	static RunnerAgent* instance();
	static void release();
	State state() const { return _state; }
	bool setup(unsigned short runner_port, unsigned short master_port,
			unsigned timeout = 2000);
	bool sendActor(const AbstractWorkerActor &actor,
			cml::TCPSocket *runner = NULL);

private:
	RunnerAgent();
	~RunnerAgent();
	static RunnerAgent* _instance;
	static pthread_mutex_t _mutex;
	State _state;
	std::vector<cml::TCPSocket *> _runners;
};

}

#endif /* RUNNERAGENT_H_ */
