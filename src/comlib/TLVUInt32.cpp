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
#include "TLVUInt32Creator.h"
#include "TLVBlock.h"
#include "TLVObjectFactoryAutoRegistor.h"

namespace cml
{

TLV_OBJECT_REGISTRATION(TLVUInt32, TLV_TYPE_UINT32, TLVUInt32Creator);

const unsigned short TLVUInt32::Size = ITLVBlock::szHeader +
		sizeof(unsigned int);

StandardTLVBlock* TLVUInt32::toTLVBlock() const
{
	StandardTLVBlock *blk = new StandardTLVBlock();
	unsigned int nv = htonl(_value);

	blk->setType(TLV_TYPE_UINT32);
	blk->setLength(sizeof(unsigned int));
	memcpy(blk->getValueBuffer(), &nv, blk->length());

	return blk;
}

}
