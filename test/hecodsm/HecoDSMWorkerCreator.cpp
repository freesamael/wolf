/**
 * \file HecoDSMWorkerCreator.cpp
 * \date Apr 15, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <CTlvObjectFactory.h>
#include <CTlvSharedMemoryInfo.h>
#include <HelperMacros.h>
#include "HecoDSMWorkerCreator.h"

using namespace wolf;
using namespace wolf;

ITlvObject* HecoDSMWorkerCreator::create(const ITlvBlock &blk) const
{
	CSharedTlvBlock sblk(blk.value());
	CTlvSharedMemoryInfo *info;
	if (!(info = dynamic_cast<CTlvSharedMemoryInfo *>(CTlvObjectFactory::instance()->
			createTLVObject(sblk)))) {
		PERR("Invalid type.");
		return NULL;
	}
	PINF_1("Meminfo: name = " << info->name() << ", size = " << info->size());
	HecoDSMWorker *c = new HecoDSMWorker();
	c->setMeminfo(info);
	return c;
}
