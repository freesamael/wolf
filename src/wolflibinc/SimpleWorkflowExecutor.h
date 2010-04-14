/**
 * \file SimpleWorkflowExecutor.h
 * \date Mar 25, 2010
 * \author samael
 */

#ifndef SIMPLEWORKFLOWEXECUTOR_H_
#define SIMPLEWORKFLOWEXECUTOR_H_

#include "IWorkflowExecutor.h"

namespace wfe
{

class SimpleWorkflowExecutor: public IWorkflowExecutor
{
public:
	void execute(const std::vector<AbstractActor *> &actors);

private:
	void setup(const std::vector<AbstractActor *> &actors);
	void iterate(const std::vector<AbstractActor *> &actors);
	void wrapup(const std::vector<AbstractActor *> &actors);
};

}

#endif /* SIMPLEWORKFLOWEXECUTOR_H_ */
