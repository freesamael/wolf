/**
 * \file DStringCreator.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "DStringCreator.h"

using namespace cml;

namespace wfe
{

ITLVObject* DStringCreator::create(const ITLVBlock &blk) const
{
	TLVString *str;
	if (!(str = dynamic_cast<TLVString *>(TLVStringCreator::create(blk)))) {
		PERR("Failed to create object.");
		return NULL;
	}

	DString *dstr = new DString(*str);
	delete str;
	return dstr;
}

}
