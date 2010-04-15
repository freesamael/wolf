/**
 * \file CounterCreator.cpp
 * \date Apr 15, 2010
 * \author samael
 */

#include <cstdio>
#include <TLVObjectFactory.h>
#include <TLVSharedMemoryInfo.h>
#include <HelperMacros.h>
#include "CounterCreator.h"

using namespace cml;
using namespace wfe;

ITLVObject* CounterCreator::create(const ITLVBlock &blk) const
{
	SharedTLVBlock sblk(blk.value());
	TLVSharedMemoryInfo *info;
	if (!(info = dynamic_cast<TLVSharedMemoryInfo *>(TLVObjectFactory::instance()->
			createTLVObject(sblk)))) {
		PERR << "Invalid type.\n";
		return NULL;
	}
	printf("%s: Meminfo: name = %s, size = %d\n", __PRETTY_FUNCTION__,
			info->name().c_str(), (int)info->size());
	Counter *c = new Counter();
	c->setMeminfo(info);
	return c;
}
