/**
 * \file CFlowUint16Creator.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "CFlowUint16Creator.h"

using namespace cml;

namespace wfe
{

ITlvObject* CFlowUint16Creator::create(const ITlvBlock &blk) const
{
	CTlvUint16 *u16;
	if (!(u16 = dynamic_cast<CTlvUint16 *>(CTlvUint16Creator::create(blk)))) {
		PERR("Failed to create object.");
		return NULL;
	}

	CFlowUint16 *du16 = new CFlowUint16(*u16);
	delete u16;
	return du16;
}

}
