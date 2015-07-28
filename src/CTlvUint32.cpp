/**
 * \file CTlvUint32.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include "CTlvUint32.h"

#include <cstring>
#include <typeinfo>
#include <arpa/inet.h>
#include "CTlvUint32Creator.h"
#include "CTlvBlock.h"
#include "CTlvObjectFactoryAutoRegistry.h"
#include "HelperMacros.h"
#include "CmlTLVTypes.h"

namespace wolf
{

TLV_OBJECT_REGISTRATION(CTlvUint32, TLV_TYPE_UINT32, CTlvUint32Creator);

const uint32_t CTlvUint32::Size = ITlvBlock::szHeader + sizeof(uint32_t);

CTlvBlock* CTlvUint32::toTLVBlock() const
{
	CTlvBlock *blk = new CTlvBlock();
	uint32_t nv = htonl(_value);

	blk->setType(TLV_TYPE_UINT32);
	blk->setLength(sizeof(uint32_t));
	memcpy(blk->value(), &nv, blk->length());

	return blk;
}

}
