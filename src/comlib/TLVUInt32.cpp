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

const unsigned short TLVUInt32::Size = ITLVBlock::szHeader +
		sizeof(unsigned int);

TLVBlock* TLVUInt32::toTLVBlock() const
{
	TLVBlock *blk = new TLVBlock();
	unsigned int nv = htonl(_value);

	blk->setType(TLV_TYPE_UINT32);
	blk->setLength(sizeof(unsigned int));
	memcpy(blk->getValueBuffer(), &nv, blk->length());

	return blk;
}

}
