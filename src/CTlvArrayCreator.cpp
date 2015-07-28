/**
 * \file CTlvArrayCreator.cpp
 * \date Apr 8, 2010
 * \author samael
 */

#include "CTlvArrayCreator.h"

#include <iostream>
#include <sstream>
#include "CTlvBlock.h"
#include "CTlvObjectFactory.h"
#include "HelperMacros.h"

namespace wolf
{

ITlvObject* CTlvArrayCreator::create(const ITlvBlock &blk) const
{
	CTlvArray *array = new CTlvArray();

	// Empty case.
	if (blk.length() == 0)
		return array;

	// Non-empty case.
	uint32_t offset = 0;
	CSharedTlvBlock *sblk = NULL;

	do {
		// Get block.
		delete sblk;
		sblk = new CSharedTlvBlock(blk.value() + offset);
		offset += sblk->plainSize();

		// Get object.
		ITlvObject *obj = CTlvObjectFactory::instance()->createTLVObject(*sblk);
		if (!obj) {
			PERR("Fail to construct an element inside the TLV blocks.");
		} else {
			array->elements().push_back(obj);
		}
	} while (sblk->plainSize() + offset < blk.length());

	delete sblk;

	return array;
}

}
