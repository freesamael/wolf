/**
 * \file CSimpleWorkflowExecutor.h
 * \date Mar 25, 2010
 * \author samael
 */

#ifndef CSIMPLEWORKFLOWEXECUTOR_H_
#define CSIMPLEWORKFLOWEXECUTOR_H_

#include <deque>
#include "CThread.h"
#include "IWorkflowExecutor.h"

namespace wolf
{

class CSimpleWorkflowExecutor: public CThread, public IWorkflowExecutor
{
public:
	void execute(const std::vector<AActor *> &actors);
	void run();
	void setup();
	void iterate();
	void wrapup();
	void findready();
	void findpost();
	void runactor(AActor *actor);
	void postrunactor(AActor *actor);

private:
	std::vector<AActor *> _all;
	std::vector<AActor *> _vwaitready;
	std::deque<AActor *> _qready;
	std::vector<AActor *> _vwaitpost;
	std::deque<AActor *> _qpost;
};

}

#endif /* CSIMPLEWORKFLOWEXECUTOR_H_ */
