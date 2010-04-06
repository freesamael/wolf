/*
 * TLVStringCreator.h
 *
 *  Created on: Mar 11, 2010
 *      Author: samael
 */

#ifndef TLVSTRINGCREATOR_H_
#define TLVSTRINGCREATOR_H_

#include "ITLVObjectCreator.h"
#include "TLVString.h"

namespace cml
{

class TLVStringCreator: public ITLVObjectCreator
{
public:
	inline ITLVObject* create() const { return new TLVString(); }
	ITLVObject* create(const ITLVBlock &blk) const;
};

}

#endif /* TLVSTRINGCREATOR_H_ */