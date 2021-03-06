/**
 * \file CFlowStringCreator.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include "CFlowStringCreator.h"

#include <iostream>
#include <sstream>
#include "HelperMacros.h"

namespace wolf
{

ITlvObject* CFlowStringCreator::create(const ITlvBlock &blk) const
{
	CTlvString *str;
	if (!(str = dynamic_cast<CTlvString *>(CTlvStringCreator::create(blk)))) {
		PERR("Failed to create object.");
		return NULL;
	}

	CFlowString *dstr = new CFlowString(*str);
	delete str;
	return dstr;
}

}
