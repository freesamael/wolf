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

const unsigned short TLVUInt16::Size = ITLVBlock::szHeader +
		sizeof(unsigned short);

StandardTLVBlock* TLVUInt16::toTLVBlock() const
{
	StandardTLVBlock *blk = new StandardTLVBlock();
	unsigned short nv = htons(_value);

	blk->setType(TLV_TYPE_UINT16);
	blk->setLength(sizeof(unsigned short));
	memcpy(blk->getValueBuffer(), &nv, blk->length());

	return blk;
}

}
