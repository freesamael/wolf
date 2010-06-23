/**
 * \file Worker.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <TLVObjectFactoryAutoRegistry.h>
#include <HelperMacros.h>
#include <ManagerActor.h>
#include "Worker.h"
#include "WorkerCreator.h"

using namespace std;
using namespace cml;
using namespace wfe;

#define TLV_TYPE_WORKER		130
TLV_OBJECT_REGISTRATION(Worker, TLV_TYPE_WORKER, WorkerCreator);

void Worker::managerInitialization(ManagerActor *manager)
{
	manager->addPort(wfe::IPort::SINK);
	manager->addPort(wfe::IPort::SOURCE);
}

void Worker::managerFinalization(ManagerActor *manager)
{
	manager->removePort(manager->sinkPorts()[0]);
	manager->removePort(manager->sourcePorts()[0]);
}

void Worker::managerPrefire(ManagerActor *manager)
{
	IDrop *d = manager->sinkPorts()[0]->readPort();
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
	manager->sourcePorts()[0]->writeChannel(n);
}

void Worker::fire()
{
	PINF_1("Old value = " << _n.value());
	_n.setValue(_n.value() + 1);
	usleep(500000); // sleep 500ms.
	PINF_1("New value = " << _n.value());
}

void Worker::update(const AbstractWorkerActor &o)
{
	const Worker *w;
	if (!(w = dynamic_cast<const Worker *>(&o))) {
		PERR("Invalid object.");
	} else {
		_n = w->_n;
	}
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
