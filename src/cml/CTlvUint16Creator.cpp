/**
 * \file CTlvUint16Creator.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <arpa/inet.h>
#include "CTlvUint16Creator.h"
#include "CTlvBlock.h"
#include "HelperMacros.h"

namespace cml
{

ITlvObject* CTlvUint16Creator::create(const ITlvBlock &blk) const
{
	// Length should always be 2 bytes.
	if (blk.length() == 2) {
		uint16_t *nv = (uint16_t *)blk.value();
		CTlvUint16 *obj = new CTlvUint16(ntohs(*nv));
		return obj;
	}
	PERR("Error: TLV length unmatched.");
	return NULL;
}

}
