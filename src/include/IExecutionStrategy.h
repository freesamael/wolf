/*
 * IExecutionStrategy.h
 *
 *  Created on: Mar 25, 2010
 *      Author: samael
 */

#ifndef IEXECUTIONSTRATEGY_H_
#define IEXECUTIONSTRATEGY_H_

#include <vector>

namespace wfe
{

class AbstractActor;

/**
 * @note Execution strategies should take care of of both normal actors and
 * iterative actors.
 */
class IExecutionStrategy
{
public:
	virtual void execute(const std::vector<AbstractActor*> &actors) = 0;
};

}

#endif /* IEXECUTIONSTRATEGY_H_ */
