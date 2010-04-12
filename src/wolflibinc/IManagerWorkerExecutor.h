#ifndef IMANAGERWORKEREXECUTOR_H_
#define IMANAGERWORKEREXECUTOR_H_

#include <vector>
#include "AbstractWorkerActor.h"

namespace wfe
{

class IManagerWorkerExecutor
{
public:
	virtual ~IManagerWorkerExecutor() {}
	virtual void execute(const std::vector<AbstractWorkerActor *> &workers) = 0;
};

}

#endif /* IMANAGERWORKEREXECUTOR_H_ */
