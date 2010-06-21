/**
 * \file Worker.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <TLVObjectFactoryAutoRegistry.h>
#include <HelperMacros.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include "Worker.h"
#include "WorkerCreator.h"

using namespace std;
using namespace cml;
using namespace wfe;

#define TLV_TYPE_WORKER		130
TLV_OBJECT_REGISTRATION(Worker, TLV_TYPE_WORKER, WorkerCreator);

void Worker::managerPrefire(ManagerActor *manager)
{
	IDrop *d = sinkPorts()[0]->readPort();
	DUInt32 *n;
	if (!(n = dynamic_cast<DUInt32 *>(d))) {
		PERR("Failed to read port.");
	} else {
		_n.setValue(n->value());
	}
	delete d;
}

void Worker::managerPostfire(ManagerActor *manager)
{
	DUInt32 *n = new DUInt32(_n);
	sourcePorts()[0]->writeChannel(n);
}

void Worker::fire()
{
	_n.setValue(_n.value() + 1);
}

StandardTLVBlock* Worker::toTLVBlock() const
{
	StandardTLVBlock *nblk = _n.toTLVBlock();
	StandardTLVBlock *blk = new StandardTLVBlock(TLV_TYPE_WORKER,
			nblk->plainSize());

	memcpy(blk->value(), nblk->plainBuffer(), blk->length());
	delete nblk;
	return blk;
}
