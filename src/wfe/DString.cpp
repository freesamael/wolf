/**
 * \file DString.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include "TLVObjectFactoryAutoRegistry.h"
#include "HelperMacros.h"
#include "DString.h"
#include "WfeTLVTypes.h"
#include "DStringCreator.h"

using namespace cml;

namespace wfe
{

TLV_OBJECT_REGISTRATION(DString, TLV_TYPE_DSTRING, DStringCreator);

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
