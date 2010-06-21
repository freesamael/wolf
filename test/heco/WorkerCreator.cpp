/**
 * \file WorkerCreator.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <HelperMacros.h>
#include <TLVObjectFactory.h>
#include "WorkerCreator.h"
#include "DUInt32.h"

using namespace cml;
using namespace wfe;

ITLVObject* WorkerCreator::create(const ITLVBlock &blk) const
{
	SharedTLVBlock sblk(blk.value());
	DUInt32 *u32;
	if (!(u32 = dynamic_cast<DUInt32 *>(TLVObjectFactory::instance()->
			createTLVObject(sblk)))) {
		PERR("Failed to create object.");
		return NULL;
	}

	Worker *w = new Worker;
	w->setNum(*u32);
	delete u32;
	return w;
}
