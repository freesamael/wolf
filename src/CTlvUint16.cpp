/**
 * \file CTlvUint16.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include "CTlvUint16.h"

#include <cstring>
#include <typeinfo>
#include <arpa/inet.h>
#include "CTlvUint16Creator.h"
#include "CTlvObjectFactoryAutoRegistry.h"
#include "CTlvBlock.h"
#include "HelperMacros.h"
#include "CmlTLVTypes.h"

namespace wolf
{

TLV_OBJECT_REGISTRATION(CTlvUint16, TLV_TYPE_UINT16, CTlvUint16Creator);

const uint32_t CTlvUint16::Size = ITlvBlock::szHeader +
		sizeof(uint16_t);

CTlvBlock* CTlvUint16::toTLVBlock() const
{
	CTlvBlock *blk = new CTlvBlock();
	uint16_t nv = htons(_value);

	blk->setType(TLV_TYPE_UINT16);
	blk->setLength(sizeof(uint16_t));
	memcpy(blk->value(), &nv, blk->length());

	return blk;
}

}
