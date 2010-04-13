/**
 * \file TLVSharedMemoryInfoCreator.cpp
 * \date Apr 8, 2010
 * \author samael
 */

#include <cstdio>
#include <TLVBlock.h>
#include <TLVString.h>
#include <TLVUInt32.h>
#include <TLVObjectFactory.h>
#include "TLVSharedMemoryInfoCreator.h"

using namespace cml;

namespace wfe
{

ITLVObject* TLVSharedMemoryInfoCreator::create(const ITLVBlock &blk) const
{
	if (blk.length() < ITLVBlock::szHeader * 2) {
		fprintf(stderr, "TLVSharedMemoryInfoCreator::create(): Error: TLV block size is too small.\n");
		return NULL;
	}

	// Get name.
	SharedTLVBlock nblk(blk.value());
	if (blk.length() < nblk.plainSize() + TLVUInt32::Size) {
		fprintf(stderr, "TLVSharedMemoryInfoCreator::create(): Error: TLV block size is too small.\n");
		return NULL;
	}
	TLVString *name;
	if (!(name = dynamic_cast<TLVString *>(TLVObjectFactory::instance()->
			createTLVObject(nblk)))) {
		fprintf(stderr, "TLVSharedMemoryInfoCreator::create(): Error: Unable to construct name string from TLV block.\n");
		return NULL;
	}

	// Get size.
	SharedTLVBlock sblk(blk.value() + nblk.plainSize());
	TLVUInt32 *u32;
	if (!(u32 = dynamic_cast<TLVUInt32 *>(TLVObjectFactory::instance()->
			createTLVObject(sblk)))) {
		fprintf(stderr, "TLVSharedMemoryInfoCreator::create(): Error: Unable to construct size value from TLV block.\n");
		return NULL;
	}

	// Thank god it successes.
	TLVSharedMemoryInfo *sminfo = new TLVSharedMemoryInfo(name->toString(), u32->value());
	delete name;
	delete u32;

	return sminfo;
}

}
