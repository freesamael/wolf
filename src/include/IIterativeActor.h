/*
 * IIterativeActor.h
 *
 *  Created on: Mar 28, 2010
 *      Author: samael
 */

#ifndef IITERATIVEACTOR_H_
#define IITERATIVEACTOR_H_

#include "IActor.h"

namespace wfe
{

/**
 * @class IIterativeActor.
 * @brief Scheduler should continuously call fire() until firecond() is false.
 */
class IIterativeActor: public IActor
{
public:
	virtual ~IIterativeActor() {}
	virtual bool firecond() const = 0;
};

}

#endif /* IITERATIVEACTOR_H_ */
