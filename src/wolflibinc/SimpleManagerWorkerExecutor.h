#ifndef SIMPLEMANAGERWORKEREXECUTOR_H_
#define SIMPLEMANAGERWORKEREXECUTOR_H_

#include "IManagerWorkerExecutor.h"

namespace wfe
{

class SimpleManagerWorkerExecutor: public IManagerWorkerExecutor
{
public:
	void execute(const std::vector<AbstractWorkerActor *> &workers);
};

}

#endif /* SIMPLEMANAGERWORKEREXECUTOR_H_ */
