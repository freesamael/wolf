/*
 * SimpleExecutionStrategy.h
 *
 *  Created on: Mar 25, 2010
 *      Author: samael
 */

#ifndef SIMPLEEXECUTIONSTRATEGY_H_
#define SIMPLEEXECUTIONSTRATEGY_H_

#include "IExecutionStrategy.h"

namespace wfe
{

class SimpleExecutionStrategy: public IExecutionStrategy
{
public:
	void execute(const std::vector<IActor *> &actors);
};

}

#endif /* SIMPLEEXECUTIONSTRATEGY_H_ */
