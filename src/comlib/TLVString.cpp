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
#include "TLVBlock.h"
#include "TLVObjectFactory.h"

using namespace std;

namespace cml
{

TLVBlock* TLVString::toTLVBlock() const
{
	if (!_str.empty()) {
		TLVBlock *blk = new TLVBlock();
		blk->setType(TLVObjectFactory::instance()->
				lookupTypeId(typeid(*this).name()));
		blk->setLength(_str.length());
		// TLV doesn't need to be null-terminated.
		char *dst = blk->getValueBuffer();
		strncpy(dst, _str.c_str(), blk->length());
		return blk;
	}
	fprintf(stderr, "TLVString::toTLVBlock(): Error: String is empty.\n");
	return NULL;
}

}
