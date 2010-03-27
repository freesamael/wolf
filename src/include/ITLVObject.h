/*
 * ITLVObject.h
 *
 *  Created on: Mar 10, 2010
 *      Author: samael
 */

#ifndef ITLVOBJECT_H_
#define ITLVOBJECT_H_

#include <cstddef>

namespace cml
{

class TLVBlock;
class ITLVObject
{
public:
	virtual ~ITLVObject() {}
	virtual TLVBlock* toTLVBlock() const = 0;
};

}

#endif /* ITLVOBJECT_H_ */
