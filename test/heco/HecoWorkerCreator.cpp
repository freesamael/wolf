/**
 * \file HecoWorkerCreator.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <HelperMacros.h>
#include <CTlvObjectFactory.h>
#include "HecoWorkerCreator.h"
#include "CFlowUint32.h"

using namespace cml;
using namespace wfe;

ITlvObject* HecoWorkerCreator::create(const ITlvBlock &blk) const
{
	CSharedTlvBlock sblk(blk.value());
	CFlowUint32 *u32;
	if (!(u32 = dynamic_cast<CFlowUint32 *>(CTlvObjectFactory::instance()->
			createTLVObject(sblk)))) {
		PERR("Failed to create object.");
		return NULL;
	}

	HecoWorker *w = new HecoWorker;
	w->setNum(*u32);
	delete u32;
	return w;
}
