/**
 * \file TLVUInt32.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <cstring>
#include <typeinfo>
#include <arpa/inet.h>
#include "TLVUInt32.h"
#include "TLVUInt32Creator.h"
#include "TLVBlock.h"
#include "TLVObjectFactoryAutoRegistry.h"
#include "HelperMacros.h"
#include "CmlTLVTypes.h"

namespace cml
{

TLV_OBJECT_REGISTRATION(TLVUInt32, TLV_TYPE_UINT32, TLVUInt32Creator);

const uint16_t TLVUInt32::Size = ITLVBlock::szHeader + sizeof(uint32_t);

StandardTLVBlock* TLVUInt32::toTLVBlock() const
{
	StandardTLVBlock *blk = new StandardTLVBlock();
	uint32_t nv = htonl(_value);

	blk->setType(TLV_TYPE_UINT32);
	blk->setLength(sizeof(uint32_t));
	memcpy(blk->value(), &nv, blk->length());

	return blk;
}

}
