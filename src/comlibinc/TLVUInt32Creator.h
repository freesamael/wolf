/*
 * TLVUInt32Creator.h
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#ifndef TLVUINT32CREATOR_H_
#define TLVUINT32CREATOR_H_

#include "ITLVObjectCreator.h"
#include "TLVUInt32.h"

#define TLV_TYPE_UINT32		3

namespace cml
{

class TLVUInt32Creator: public ITLVObjectCreator
{
public:
	ITLVObject* create() const { return new TLVUInt32(); }
	ITLVObject* create(const TLVBlock &blk) const;
};

}

#endif /* TLVUINT32CREATOR_H_ */
