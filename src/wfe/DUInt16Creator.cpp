/**
 * \file DUInt16Creator.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "DUInt16Creator.h"

using namespace cml;

namespace wfe
{

ITLVObject* DUInt16Creator::create(const ITLVBlock &blk) const
{
	TLVUInt16 *u16;
	if (!(u16 = dynamic_cast<TLVUInt16 *>(TLVUInt16Creator::create(blk)))) {
		PERR("Failed to create object.");
		return NULL;
	}

	DUInt16 *du16 = new DUInt16(*u16);
	delete u16;
	return du16;
}

}
