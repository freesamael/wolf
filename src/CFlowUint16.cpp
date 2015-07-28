/**
 * \file CFlowUint16.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include "CFlowUint16.h"

#include "CTlvObjectFactoryAutoRegistry.h"
#include "HelperMacros.h"
#include "WfeTLVTypes.h"
#include "CFlowUint16Creator.h"

namespace wolf
{

TLV_OBJECT_REGISTRATION(CFlowUint16, TLV_TYPE_DUINT16, CFlowUint16Creator);

CTlvBlock* CFlowUint16::toTLVBlock() const
{
	CTlvBlock *blk = CTlvUint16::toTLVBlock();
	blk->setType(TLV_TYPE_DUINT16);
	return blk;
}

IDrop* CFlowUint16::clone() const
{
	return new CFlowUint16(*this);
}

}
