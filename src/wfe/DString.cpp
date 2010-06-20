/**
 * \file DString.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include "DString.h"
#include "WfeTLVTypes.h"

using namespace cml;

namespace wfe
{

StandardTLVBlock* DString::toTLVBlock() const
{
	StandardTLVBlock *blk = TLVString::toTLVBlock();
	blk->setType(TLV_TYPE_DSTRING);
	return blk;
}

IDrop* DString::clone() const
{
	return new DString(*this);
}

}
