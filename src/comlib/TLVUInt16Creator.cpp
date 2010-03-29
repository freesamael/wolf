/*
 * TLVUInt16Creator.cpp
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#include <cstdio>
#include <arpa/inet.h>
#include "TLVUInt16Creator.h"
#include "TLVBlock.h"

namespace cml
{

ITLVObject* TLVUInt16Creator::create(const TLVBlock &blk) const
{
	// Length should always be 2 bytes.
	if (blk.length() == 2) {
		unsigned short *nv = (unsigned short *)blk.getValueBuffer();
		TLVUInt16 *obj = new TLVUInt16(ntohs(*nv));
		return obj;
	}
	fprintf(stderr, "TLVUInt16Creator::create(): Error: TLV length unmatched.\n");
	return NULL;
}

}
