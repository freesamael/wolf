/*
 * TLVUInt32.cpp
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#include <cstring>
#include <typeinfo>
#include <arpa/inet.h>
#include "TLVUInt32.h"
#include "TLVBlock.h"
#include "TLVObjectFactory.h"

namespace cml
{

TLVBlock* TLVUInt32::toTLVBlock() const
{
	TLVBlock *blk = new TLVBlock();
	unsigned int nv = htonl(_value);

	blk->setType(TLVObjectFactory::instance()->
			lookupTypeId(typeid(*this).name()));
	blk->setLength(4);
	memcpy(blk->getValueBuffer(), &nv, blk->length());

	return blk;
}

}
