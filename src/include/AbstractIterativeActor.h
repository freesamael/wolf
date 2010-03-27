/*
 * AbstractIterativeActor.h
 *
 *  Created on: Mar 27, 2010
 *      Author: samael
 */

#ifndef ABSTRACTITERATIVEACTOR_H_
#define ABSTRACTITERATIVEACTOR_H_

#include "AbstractActor.h"

namespace wfe
{

class AbstractIterativeActor: public AbstractActor
{
public:
	AbstractIterativeActor() {}
	virtual ~AbstractIterativeActor() {}
	virtual bool fireCond() = 0;
};

}

#endif /* ABSTRACTITERATIVEACTOR_H_ */
