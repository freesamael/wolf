/**
 * \file TLVUInt16.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <cstring>
#include <typeinfo>
#include <arpa/inet.h>
#include "TLVUInt16.h"
#include "TLVUInt16Creator.h"
#include "TLVObjectFactoryAutoRegistry.h"
#include "TLVBlock.h"
#include "HelperMacros.h"
#include "CmlTLVTypes.h"

namespace cml
{

TLV_OBJECT_REGISTRATION(TLVUInt16, TLV_TYPE_UINT16, TLVUInt16Creator);

const uint16_t TLVUInt16::Size = ITLVBlock::szHeader +
		sizeof(uint16_t);

StandardTLVBlock* TLVUInt16::toTLVBlock() const
{
	StandardTLVBlock *blk = new StandardTLVBlock();
	uint16_t nv = htons(_value);

	blk->setType(TLV_TYPE_UINT16);
	blk->setLength(sizeof(uint16_t));
	memcpy(blk->value(), &nv, blk->length());

	return blk;
}

}
