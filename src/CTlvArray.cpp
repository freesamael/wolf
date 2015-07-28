/**
 * \file CTlvArray.cpp
 * \date Apr 8, 2010
 * \author samael
 */

#include "CTlvArray.h"

#include <typeinfo>
#include "CTlvArrayCreator.h"
#include "CTlvObjectFactoryAutoRegistry.h"
#include "HelperMacros.h"
#include "CmlTLVTypes.h"

using namespace std;

namespace wolf
{

TLV_OBJECT_REGISTRATION(CTlvArray, TLV_TYPE_ARRAY, CTlvArrayCreator);

/**
 * Generate a TLV block of blocks (nested TLV blocks).
 */
CTlvBlock* CTlvArray::toTLVBlock() const
{
	// Generate all blocks of elements.
	vector<const ITlvBlock *> blocks;
	for (unsigned i = 0; i < _elem.size(); i++)
		blocks.push_back(_elem[i]->toTLVBlock());

	// Concatenate blocks.
	CTlvBlock *blk = CTlvBlock::concate(blocks);
	blk->setType(TLV_TYPE_ARRAY);

	// Cleanup.
	for (unsigned i = 0; i < blocks.size(); i++)
		delete blocks[i];

	return blk;
}

}
