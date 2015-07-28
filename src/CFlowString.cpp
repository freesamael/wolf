/**
 * \file CFlowString.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include "CFlowString.h"

#include "CTlvObjectFactoryAutoRegistry.h"
#include "HelperMacros.h"
#include "WfeTLVTypes.h"
#include "CFlowStringCreator.h"

namespace wolf
{

TLV_OBJECT_REGISTRATION(CFlowString, TLV_TYPE_DSTRING, CFlowStringCreator);

CTlvBlock* CFlowString::toTLVBlock() const
{
	CTlvBlock *blk = CTlvString::toTLVBlock();
	blk->setType(TLV_TYPE_DSTRING);
	return blk;
}

IDrop* CFlowString::clone() const
{
	return new CFlowString(*this);
}

}
