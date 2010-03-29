/*
 * TLVUInt16.cpp
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#include <cstring>
#include <typeinfo>
#include <arpa/inet.h>
#include "TLVUInt16.h"
#include "TLVObjectFactory.h"
#include "TLVBlock.h"

namespace cml
{

TLVBlock* TLVUInt16::toTLVBlock() const
{
	TLVBlock *blk = new TLVBlock();
	unsigned short nv = htons(_value);

	blk->setType(TLVObjectFactory::instance()->
			lookupTypeId(typeid(*this).name()));
	blk->setLength(2);
	memcpy(blk->getValueBuffer(), &nv, blk->length());

	return blk;
}

}
