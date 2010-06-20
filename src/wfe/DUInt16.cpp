/**
 * \file DUInt16.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include "DUInt16.h"
#include "WfeTLVTypes.h"

using namespace cml;

namespace wfe
{

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
