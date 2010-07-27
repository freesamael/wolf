/**
 * \file CTlvString.cpp
 * \date Mar 10, 2010
 * \author samael
 */

#include <cstring>
#include <typeinfo>
#include "CTlvString.h"
#include "CTlvStringCreator.h"
#include "CTlvBlock.h"
#include "CTlvObjectFactoryAutoRegistry.h"
#include "HelperMacros.h"
#include "CmlTLVTypes.h"

using namespace std;

namespace wolf
{

TLV_OBJECT_REGISTRATION(CTlvString, TLV_TYPE_STRING, CTlvStringCreator);

CTlvBlock* CTlvString::toTLVBlock() const
{
	CTlvBlock *blk = new CTlvBlock();
	blk->setType(TLV_TYPE_STRING);
	blk->setLength(_str.length());
	// TLV doesn't need to be null-terminated.
	char *dst = blk->value();
	strncpy(dst, _str.c_str(), blk->length());
	return blk;
}

}
