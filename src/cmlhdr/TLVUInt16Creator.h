/**
 * \file TLVUInt16Creator.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef TLVUINT16CREATOR_H_
#define TLVUINT16CREATOR_H_

#include "ITLVObjectCreator.h"
#include "TLVUInt16.h"

namespace cml
{

/**
 * Creator for TLVUInt16.
 */
class TLVUInt16Creator: public ITLVObjectCreator
{
public:
	inline ITLVObject* create() const { return new TLVUInt16(); }
	ITLVObject* create(const ITLVBlock &blk) const;
};

}

#endif /* TLVUINT16CREATOR_H_ */
