/**
 * \file TLVArrayCreator.cpp
 * \date Apr 8, 2010
 * \author samael
 */

#include <cstdio>
#include "TLVArrayCreator.h"
#include "TLVBlock.h"
#include "TLVObjectFactory.h"
#include "HelperMacros.h"

namespace cml
{

ITLVObject* TLVArrayCreator::create(const ITLVBlock &blk) const
{
	TLVArray *array = new TLVArray();

	// Empty case.
	if (blk.length() == 0)
		return array;

	// Non-empty case.
	uint16_t offset = 0;
	SharedTLVBlock *sblk = NULL;

	do {
		// Get block.
		delete sblk;
		sblk = new SharedTLVBlock(blk.value() + offset);
		offset += sblk->plainSize();

		// Get object.
		ITLVObject *obj = TLVObjectFactory::instance()->createTLVObject(*sblk);
		if (!obj)
			PERR("Fail to construct an element inside the TLV blocks.");
		else
			array->elements().push_back(obj);
	} while (sblk->plainSize() + offset < blk.length());

	delete sblk;

	return array;
}

}
