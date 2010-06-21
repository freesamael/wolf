/**
 * \file TLVUInt16Creator.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <arpa/inet.h>
#include "TLVUInt16Creator.h"
#include "TLVBlock.h"
#include "HelperMacros.h"

namespace cml
{

ITLVObject* TLVUInt16Creator::create(const ITLVBlock &blk) const
{
	// Length should always be 2 bytes.
	if (blk.length() == 2) {
		uint16_t *nv = (uint16_t *)blk.value();
		TLVUInt16 *obj = new TLVUInt16(ntohs(*nv));
		return obj;
	}
	PERR("Error: TLV length unmatched.");
	return NULL;
}

}
