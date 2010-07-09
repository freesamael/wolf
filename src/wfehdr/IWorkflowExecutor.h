/**
 * \file IWorkflowExecutor.h
 * \date Mar 25, 2010
 * \author samael
 */

#ifndef IWORKFLOWEXECUTOR_H_
#define IWORKFLOWEXECUTOR_H_

#include <vector>
#include "AActor.h"

namespace wfe
{

/**
 * \interface
 * \note
 * Execution strategies should be aware of of both normal actors and
 * iterative actors.
 */
class IWorkflowExecutor
{
public:
	virtual ~IWorkflowExecutor() {}
	virtual void execute(const std::vector<AActor *> &actors) = 0;
};

}

#endif /* IWORKFLOWEXECUTOR_H_ */
