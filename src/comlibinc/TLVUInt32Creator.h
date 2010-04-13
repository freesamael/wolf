/**
 * \file TLVUInt32Creator.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef TLVUINT32CREATOR_H_
#define TLVUINT32CREATOR_H_

#include "ITLVObjectCreator.h"
#include "TLVUInt32.h"

namespace cml
{

/**
 * Creator for TLVUInt32.
 */
class TLVUInt32Creator: public ITLVObjectCreator
{
public:
	ITLVObject* create() const { return new TLVUInt32(); }
	ITLVObject* create(const ITLVBlock &blk) const;
};

}

#endif /* TLVUINT32CREATOR_H_ */
