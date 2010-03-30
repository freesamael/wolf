/*
 * ITLVObjectCreator.h
 *
 *  Created on: Mar 10, 2010
 *      Author: samael
 */

#ifndef ITLVOBJECTCREATOR_H_
#define ITLVOBJECTCREATOR_H_

#include "ITLVObject.h"
#include "ITLVBlock.h"

namespace cml
{

class ITLVObjectCreator
{
public:
	virtual ~ITLVObjectCreator() {}
	virtual ITLVObject* create() const = 0;
	virtual ITLVObject* create(const ITLVBlock &blk) const = 0;
};

}

#endif /* ITLVOBJECTCREATOR_H_ */
