/*
 * TLVUInt32Creator.cpp
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#include <cstdio>
#include <arpa/inet.h>
#include "TLVUInt32Creator.h"
#include "TLVBlock.h"

namespace cml
{

ITLVObject* TLVUInt32Creator::create(const ITLVBlock &blk) const
{
	// Length should always be 4 bytes.
	if (blk.length() == 4) {
		unsigned int *nv = (unsigned int *)blk.value();
		TLVUInt32 *obj = new TLVUInt32(ntohl(*nv));
		return obj;
	}
	fprintf(stderr, "TLVUInt32Creator::create(): Error: TLV length unmatched.\n");
	return NULL;
}

}
