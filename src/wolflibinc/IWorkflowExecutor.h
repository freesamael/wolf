/**
 * \file IWorkflowExecutor.h
 * \date Mar 25, 2010
 * \author samael
 */

#ifndef IWORKFLOWEXECUTOR_H_
#define IWORKFLOWEXECUTOR_H_

#include <vector>
#include "AbstractActor.h"

namespace wfe
{

/**
 * \note
 * Execution strategies should be aware of of both normal actors and
 * iterative actors.
 */
class IWorkflowExecutor
{
public:
	virtual ~IWorkflowExecutor() {}
	virtual void execute(const std::vector<AbstractActor *> &actors) = 0;
};

}

#endif /* IWORKFLOWEXECUTOR_H_ */
