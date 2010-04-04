/*
 * SimpleManagerWorkerExecutor.h
 *
 *  Created on: Apr 4, 2010
 *      Author: samael
 */

#ifndef SIMPLEMANAGERWORKEREXECUTOR_H_
#define SIMPLEMANAGERWORKEREXECUTOR_H_

#include "IManagerWorkerExecutor.h"
#include "RunnerAgent.h"

namespace wfe
{

class SimpleManagerWorkerExecutor: public IManagerWorkerExecutor
{
public:
	SimpleManagerWorkerExecutor(RunnerAgent *agent): _agent(agent) {}
	void execute(const std::vector<AbstractWorkerActor *> &workers);

private:
	RunnerAgent *_agent;
};

}

#endif /* SIMPLEMANAGERWORKEREXECUTOR_H_ */
