/**
 * \file TLVUInt32Creator.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <iostream>
#include <arpa/inet.h>
#include "TLVUInt32Creator.h"
#include "TLVBlock.h"
#include "HelperMacros.h"

namespace cml
{

ITLVObject* TLVUInt32Creator::create(const ITLVBlock &blk) const
{
	// Length should always be 4 bytes.
	if (blk.length() == 4) {
		uint32_t *nv = (uint32_t *)blk.value();
		TLVUInt32 *obj = new TLVUInt32(ntohl(*nv));
		return obj;
	}
	PERR("TLV length unmatched.");
	return NULL;
}

}
