/**
 * \file CounterCreator.cpp
 * \date Apr 15, 2010
 * \author samael
 */

#include <TLVObjectFactory.h>
#include <TLVSharedMemoryInfo.h>
#include <HelperMacros.h>
#include "CounterCreator.h"

using namespace cml;
using namespace wfe;

ITLVObject* CounterCreator::create(const ITLVBlock &blk) const
{
	TLVSharedMemoryInfo *info;
	if (!(info = dynamic_cast<TLVSharedMemoryInfo *>(TLVObjectFactory::instance()->
			createTLVObject(blk.value())))) {
		PERR << "Invalid type.\n";
		return NULL;
	}
	Counter *c = new Counter();
	c->setMeminfo(info);
	return c;
}
