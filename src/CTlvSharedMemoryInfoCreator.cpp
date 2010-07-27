/**
 * \file CTlvSharedMemoryInfoCreator.cpp
 * \date Apr 8, 2010
 * \author samael
 */

#include <iostream>
#include "CTlvBlock.h"
#include "CTlvString.h"
#include "CTlvUint32.h"
#include "CTlvObjectFactory.h"
#include "HelperMacros.h"
#include "CTlvSharedMemoryInfoCreator.h"

using namespace wolf;

namespace wolf
{

ITlvObject* CTlvSharedMemoryInfoCreator::create(const ITlvBlock &blk) const
{
	if (blk.length() < ITlvBlock::szHeader * 2) {
		PERR("TLV block size is too small.");
		return NULL;
	}

	// Get name.
	CSharedTlvBlock nblk(blk.value());
	if (blk.length() < nblk.plainSize() + CTlvUint32::Size) {
		PERR("TLV block size is too small.");
		return NULL;
	}
	CTlvString *name;
	if (!(name = dynamic_cast<CTlvString *>(CTlvObjectFactory::instance()->
			createTLVObject(nblk)))) {
		PERR("Unable to construct name string from TLV block.");
		return NULL;
	}

	// Get size.
	CSharedTlvBlock sblk(blk.value() + nblk.plainSize());
	CTlvUint32 *u32;
	if (!(u32 = dynamic_cast<CTlvUint32 *>(CTlvObjectFactory::instance()->
			createTLVObject(sblk)))) {
		PERR("Unable to construct size value from TLV block.");
		return NULL;
	}

	// Thank god it successes.
	CTlvSharedMemoryInfo *sminfo = new CTlvSharedMemoryInfo(name->toString(), u32->value());
	delete name;
	delete u32;

	return sminfo;
}

}
