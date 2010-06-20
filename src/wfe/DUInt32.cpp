/**
 * \file DUInt32.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include "DUInt32.h"
#include "WfeTLVTypes.h"

using namespace cml;

namespace wfe
{

StandardTLVBlock* DUInt32::toTLVBlock() const
{
	StandardTLVBlock *blk = TLVUInt32::toTLVBlock();
	blk->setType(TLV_TYPE_DUINT32);
	return blk;
}

IDrop* DUInt32::clone() const
{
	return new DUInt32(*this);
}

}
