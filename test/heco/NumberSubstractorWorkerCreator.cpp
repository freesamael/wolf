/*
 * NumberSubstractorWorkerCreator.cpp
 *
 *  Created on: Apr 10, 2010
 *      Author: samael
 */

#include <cstdio>
#include <TLVObjectFactory.h>
#include <TLVBlock.h>
#include "NumberSubstractorWorkerCreator.h"
#include "NumberSubstractorWorker.h"

using namespace cml;
using namespace wfe;

ITLVObject* NumberSubstractorWorkerCreator::create() const
{
	return new NumberSubstractorWorker();
}

ITLVObject* NumberSubstractorWorkerCreator::create(const ITLVBlock &blk) const
{
	if (blk.length() == 0)
		return new NumberSubstractorWorker();

	SharedTLVBlock sblk(blk.value());
	ITLVObject *obj = TLVObjectFactory::instance()->createTLVObject(sblk);
	TLVSharedMemoryInfo *sminfo;
	if (!(sminfo = dynamic_cast<TLVSharedMemoryInfo *>(obj))) {
		fprintf(stderr, "NumberSubstractorWorkerCreator::create(): Error: Unable to construct shared memory info.\n");
		delete obj;
		return NULL;
	}

	return new NumberSubstractorWorker(sminfo);
}
