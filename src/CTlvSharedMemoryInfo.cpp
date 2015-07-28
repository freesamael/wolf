/**
 * \file CTlvSharedMemoryInfo.cpp
 * \date Apr 8, 2010
 * \author samael
 */

#include "CTlvSharedMemoryInfo.h"

#include <typeinfo>
#include <vector>
#include "CTlvBlock.h"
#include "CTlvString.h"
#include "CTlvUint32.h"
#include "CTlvObjectFactoryAutoRegistry.h"
#include "HelperMacros.h"
#include "CTlvSharedMemoryInfoCreator.h"
#include "WfeTLVTypes.h"

using namespace std;

namespace wolf
{

TLV_OBJECT_REGISTRATION(CTlvSharedMemoryInfo, TLV_TYPE_SMINFO, CTlvSharedMemoryInfoCreator);

CTlvBlock* CTlvSharedMemoryInfo::toTLVBlock() const
{
	vector<const ITlvBlock*> blocks;
	blocks.push_back(CTlvString(_name).toTLVBlock());
	blocks.push_back(CTlvUint32((uint32_t)_size).toTLVBlock());

	CTlvBlock *blk = CTlvBlock::concate(blocks);
	blk->setType(TLV_TYPE_SMINFO);

	delete blocks[0];
	delete blocks[1];

	return blk;
}

}
