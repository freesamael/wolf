/*
 * TLVString.cpp
 *
 *  Created on: Mar 10, 2010
 *      Author: samael
 */

#include <cstdio>
#include <cstring>
#include <typeinfo>
#include "TLVString.h"
#include "TLVStringCreator.h"
#include "TLVBlock.h"
#include "TLVObjectFactoryAutoRegistry.h"
#include "HelperMacros.h"
#include "CmlTLVTypes.h"

using namespace std;

namespace cml
{

TLV_OBJECT_REGISTRATION(TLVString, TLV_TYPE_STRING, TLVStringCreator);

StandardTLVBlock* TLVString::toTLVBlock() const
{
	StandardTLVBlock *blk = new StandardTLVBlock();
	blk->setType(TLV_TYPE_STRING);
	blk->setLength(_str.length());
	// TLV doesn't need to be null-terminated.
	char *dst = blk->value();
	strncpy(dst, _str.c_str(), blk->length());
	return blk;
}

}
