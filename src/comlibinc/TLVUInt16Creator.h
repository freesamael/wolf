/*
 * TLVUInt16Creator.h
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#ifndef TLVUINT16CREATOR_H_
#define TLVUINT16CREATOR_H_

#include "ITLVObjectCreator.h"
#include "TLVUInt16.h"

#define TLV_TYPE_UINT16		2

namespace cml
{

class TLVUInt16Creator: public ITLVObjectCreator
{
public:
	inline ITLVObject* create() const { return new TLVUInt16(); }
	ITLVObject* create(const TLVBlock &blk) const;
};

}

#endif /* TLVUINT16CREATOR_H_ */
