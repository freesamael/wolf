/*
 * TLVArrayCreator.h
 *
 *  Created on: Apr 8, 2010
 *      Author: samael
 */

#ifndef TLVARRAYCREATOR_H_
#define TLVARRAYCREATOR_H_

#include "ITLVObjectCreator.h"
#include "TLVArray.h"

namespace cml
{

/**
 * The creator for TLVArray.
 */
class TLVArrayCreator: public ITLVObjectCreator
{
public:
	ITLVObject* create() const { return new TLVArray(); }
	ITLVObject* create(const ITLVBlock &blk) const;
};

}

#endif /* TLVARRAYCREATOR_H_ */
