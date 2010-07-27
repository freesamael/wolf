/**
 * \file CFlowUint32Creator.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "CFlowUint32Creator.h"

using namespace wolf;

namespace wolf
{

ITlvObject* CFlowUint32Creator::create(const ITlvBlock &blk) const
{
	CTlvUint32 *u32;
	if (!(u32 = dynamic_cast<CTlvUint32 *>(CTlvUint32Creator::create(blk)))) {
		PERR("Failed to create object.");
		return NULL;
	}

	CFlowUint32 *du32 = new CFlowUint32(*u32);
	delete u32;
	return du32;
}

}
