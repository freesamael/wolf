/**
 * \file HecoDSMWorkerCreator.cpp
 * \date Apr 15, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <TLVObjectFactory.h>
#include <TLVSharedMemoryInfo.h>
#include <HelperMacros.h>
#include "HecoDSMWorkerCreator.h"

using namespace cml;
using namespace wfe;

ITLVObject* HecoDSMWorkerCreator::create(const ITLVBlock &blk) const
{
	SharedTLVBlock sblk(blk.value());
	TLVSharedMemoryInfo *info;
	if (!(info = dynamic_cast<TLVSharedMemoryInfo *>(TLVObjectFactory::instance()->
			createTLVObject(sblk)))) {
		PERR("Invalid type.");
		return NULL;
	}
	PINF_1("Meminfo: name = " << info->name() << ", size = " << info->size());
	HecoDSMWorker *c = new HecoDSMWorker();
	c->setMeminfo(info);
	return c;
}
