/**
 * \file CFlowUint32.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include "CTlvObjectFactoryAutoRegistry.h"
#include "HelperMacros.h"
#include "CFlowUint32.h"
#include "WfeTLVTypes.h"
#include "CFlowUint32Creator.h"

using namespace cml;

namespace wfe
{

TLV_OBJECT_REGISTRATION(CFlowUint32, TLV_TYPE_DUINT32, CFlowUint32Creator);

CTlvBlock* CFlowUint32::toTLVBlock() const
{
	CTlvBlock *blk = CTlvUint32::toTLVBlock();
	blk->setType(TLV_TYPE_DUINT32);
	return blk;
}

IDrop* CFlowUint32::clone() const
{
	return new CFlowUint32(*this);
}

}