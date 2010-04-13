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
	void execute(const std::vector<IActor *> &actors);
};

}

#endif /* SIMPLEWORKFLOWEXECUTOR_H_ */
