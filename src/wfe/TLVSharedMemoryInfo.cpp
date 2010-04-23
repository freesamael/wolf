/**
 * \file TLVSharedMemoryInfo.cpp
 * \date Apr 8, 2010
 * \author samael
 */

#include <typeinfo>
#include <vector>
#include <TLVBlock.h>
#include <TLVString.h>
#include <TLVUInt32.h>
#include <TLVObjectFactoryAutoRegistry.h>
#include <HelperMacros.h>
#include "TLVSharedMemoryInfo.h"
#include "TLVSharedMemoryInfoCreator.h"
#include "WfeTLVTypes.h"

using namespace std;
using namespace cml;

namespace wfe
{

TLV_OBJECT_REGISTRATION(TLVSharedMemoryInfo, TLV_TYPE_SMINFO, TLVSharedMemoryInfoCreator);

StandardTLVBlock* TLVSharedMemoryInfo::toTLVBlock() const
{
	vector<const ITLVBlock*> blocks;
	blocks.push_back(TLVString(_name).toTLVBlock());
	blocks.push_back(TLVUInt32((uint32_t)_size).toTLVBlock());

	StandardTLVBlock *blk = StandardTLVBlock::concate(blocks);
	blk->setType(TLV_TYPE_SMINFO);

	delete blocks[0];
	delete blocks[1];

	return blk;
}

}