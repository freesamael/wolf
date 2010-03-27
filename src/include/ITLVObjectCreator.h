/*
 * ITLVObjectCreator.h
 *
 *  Created on: Mar 10, 2010
 *      Author: samael
 */

#ifndef ITLVOBJECTCREATOR_H_
#define ITLVOBJECTCREATOR_H_

#include "ITLVObject.h"

namespace cml
{

class TLVBlock;
class ITLVObjectCreator
{
public:
	virtual ~ITLVObjectCreator() {}
	virtual ITLVObject* create() = 0;
	virtual ITLVObject* create(const TLVBlock &blk) = 0;
};

}

#endif /* ITLVOBJECTCREATOR_H_ */
