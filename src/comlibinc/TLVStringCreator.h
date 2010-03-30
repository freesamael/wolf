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

#define TLV_TYPE_STRING		1

namespace cml
{

class TLVStringCreator: public ITLVObjectCreator
{
public:
	inline ITLVObject* create() const { return new TLVString(); }
	ITLVObject* create(const TLVBlock &blk) const;
};

}

#endif /* TLVSTRINGCREATOR_H_ */
