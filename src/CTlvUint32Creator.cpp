/**
 * \file CTlvUint32Creator.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <arpa/inet.h>
#include "CTlvUint32Creator.h"
#include "CTlvBlock.h"
#include "HelperMacros.h"

namespace wolf
{

ITlvObject* CTlvUint32Creator::create(const ITlvBlock &blk) const
{
	// Length should always be 4 bytes.
	if (blk.length() == 4) {
		uint32_t *nv = (uint32_t *)blk.value();
		CTlvUint32 *obj = new CTlvUint32(ntohl(*nv));
		return obj;
	}
	PERR("TLV length unmatched.");
	return NULL;
}

}
