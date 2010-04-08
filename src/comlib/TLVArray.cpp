/*
 * TLVArray.cpp
 *
 *  Created on: Apr 8, 2010
 *      Author: samael
 */

#include <cstring>
#include "TLVArray.h"
#include "TLVArrayCreator.h"
#include "TLVObjectFactoryAutoRegistry.h"
#include "HelperMacros.h"
#include "TLVTypes.h"

using namespace std;

namespace cml
{

TLV_OBJECT_REGISTRATION(TLVArray, TLV_TYPE_ARRAY, TLVArrayCreator);

/**
 * Generate a TLV block of blocks (nested TLV blocks).
 */
StandardTLVBlock* TLVArray::toTLVBlock() const
{
	// Generate all blocks of elements.
	vector<const ITLVBlock *> blocks;
	for (int i = 0; i < (int)_elem.size(); i++)
		blocks.push_back(_elem[i]->toTLVBlock());

	// Concatenate blocks.
	StandardTLVBlock *blk = StandardTLVBlock::concate(blocks);
	blk->setType(TLV_TYPE_ARRAY);

	// Cleanup.
	for (int i = 0; i < (int)blocks.size(); i++)
		delete blocks[i];

	return blk;
}

}
