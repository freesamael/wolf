/**
 * \file DUInt16.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include "TLVObjectFactoryAutoRegistry.h"
#include "HelperMacros.h"
#include "DUInt16.h"
#include "WfeTLVTypes.h"
#include "DUInt16Creator.h"

using namespace cml;

namespace wfe
{

TLV_OBJECT_REGISTRATION(DUInt16, TLV_TYPE_DUINT16, DUInt16Creator);

StandardTLVBlock* DUInt16::toTLVBlock() const
{
	StandardTLVBlock *blk = TLVUInt16::toTLVBlock();
	blk->setType(TLV_TYPE_DUINT16);
	return blk;
}

IDrop* DUInt16::clone() const
{
	return new DUInt16(*this);
}

}
