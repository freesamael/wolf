/*
 * ITLVObject.h
 *
 *  Created on: Mar 10, 2010
 *      Author: samael
 */

#ifndef ITLVOBJECT_H_
#define ITLVOBJECT_H_

#include <cstddef>
#include "TLVBlock.h"

namespace cml
{

class StandardTLVBlock;
class ITLVObject
{
public:
	virtual ~ITLVObject() {}
	virtual StandardTLVBlock* toTLVBlock() const = 0;
};

}

#endif /* ITLVOBJECT_H_ */
