#ifndef IWORKFLOWEXECUTOR_H_
#define IWORKFLOWEXECUTOR_H_

#include <vector>
#include "IActor.h"

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
	virtual void execute(const std::vector<IActor *> &actors) = 0;
};

}

#endif /* IWORKFLOWEXECUTOR_H_ */
