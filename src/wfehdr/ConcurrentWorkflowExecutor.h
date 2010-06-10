/**
 * \file ConcurrentWorkflowExecutor.h
 * \date Jun 10, 2010
 * \author samael
 */

#ifndef CONCURRENTWORKFLOWEXECUTOR_H_
#define CONCURRENTWORKFLOWEXECUTOR_H_

#include <vector>
#include <deque>
#include "Thread.h"
#include "Mutex.h"
#include "WaitCondition.h"
#include "IWorkflowExecutor.h"

namespace wfe
{

class ConcurrentWorkflowExecutor: public IWorkflowExecutor
{
public:
	ConcurrentWorkflowExecutor(unsigned pnum);
	~ConcurrentWorkflowExecutor();
	void execute(const std::vector<AbstractActor *> &actors);
	void updateQueue();
	AbstractActor* takeActor();
	bool isFinished() const { return _fin; }

private:
	void setup(const std::vector<AbstractActor *> &actors);
	void wrapup(const std::vector<AbstractActor *> &actors);
	bool _fin;
	std::vector<cml::Thread *> _exths;
	std::vector<AbstractActor *> _vwait;
	std::deque<AbstractActor *> _qready;
	cml::Mutex _mutex;
	cml::WaitCondition _wcond;
};

}

#endif /* CONCURRENTWORKFLOWEXECUTOR_H_ */
