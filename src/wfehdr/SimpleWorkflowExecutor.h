/**
 * \file SimpleWorkflowExecutor.h
 * \date Mar 25, 2010
 * \author samael
 */

#ifndef SIMPLEWORKFLOWEXECUTOR_H_
#define SIMPLEWORKFLOWEXECUTOR_H_

#include <deque>
#include "Thread.h"
#include "IWorkflowExecutor.h"

namespace wfe
{

class SimpleWorkflowExecutor: public IWorkflowExecutor, public cml::Thread
{
public:
	void execute(const std::vector<AbstractActor *> &actors);
	void run();
	void setup();
	void iterate();
	void wrapup();
	void findready();
	void findpost();
	void runactor(AbstractActor *actor);
	void postrunactor(AbstractActor *actor);

private:
	std::vector<AbstractActor *> _all;
	std::vector<AbstractActor *> _vwaitready;
	std::deque<AbstractActor *> _qready;
	std::vector<AbstractActor *> _vwaitpost;
	std::deque<AbstractActor *> _qpost;
};

}

#endif /* SIMPLEWORKFLOWEXECUTOR_H_ */
