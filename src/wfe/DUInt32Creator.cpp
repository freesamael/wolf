/**
 * \file DUInt32Creator.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <iostream>
#include "HelperMacros.h"
#include "DUInt32Creator.h"

using namespace cml;

namespace wfe
{

ITLVObject* DUInt32Creator::create(const ITLVBlock &blk) const
{
	TLVUInt32 *u32;
	if (!(u32 = dynamic_cast<TLVUInt32 *>(TLVUInt32Creator::create(blk)))) {
		PERR("Failed to create object.");
		return NULL;
	}

	DUInt32 *du32 = new DUInt32(*u32);
	delete u32;
	return du32;
}

}
