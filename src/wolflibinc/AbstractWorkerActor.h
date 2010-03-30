/*
 * AbstractWorkerActor.h
 *
 *  Created on: Mar 28, 2010
 *      Author: samael
 */

#ifndef ABSTRACTWORKERACTOR_H_
#define ABSTRACTWORKERACTOR_H_

#include "IIterativeActor.h"
#include "ITLVObject.h"

namespace wfe
{

class AbstractWorkerActor: public IIterativeActor, public cml::ITLVObject
{
public:
	AbstractWorkerActor();
	virtual ~AbstractWorkerActor();
};

}

#endif /* ABSTRACTWORKERACTOR_H_ */
