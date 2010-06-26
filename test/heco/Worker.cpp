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
#include <IManagerActor.h>
#include <SimpleManagerActor.h>
#include "Worker.h"
#include "WorkerCreator.h"

using namespace std;
using namespace cml;
using namespace wfe;

#define TLV_TYPE_WORKER		130
TLV_OBJECT_REGISTRATION(Worker, TLV_TYPE_WORKER, WorkerCreator);

void Worker::managerInitialization(IManagerActor *mgr)
{
	SimpleManagerActor *smgr;
	if ((smgr = dynamic_cast<SimpleManagerActor *>(mgr))) {
		smgr->addPort(wfe::IPort::SINK);
		smgr->addPort(wfe::IPort::SOURCE);
	}
}

void Worker::managerFinalization(IManagerActor *mgr)
{
	SimpleManagerActor *smgr;
	if ((smgr = dynamic_cast<SimpleManagerActor *>(mgr))) {
		smgr->removePort(smgr->sinkPorts()[0]);
		smgr->removePort(smgr->sourcePorts()[0]);
	}
}

void Worker::managerPrefire(IManagerActor *mgr)
{
	SimpleManagerActor *smgr;
	if ((smgr = dynamic_cast<SimpleManagerActor *>(mgr))) {
		IDrop *d = smgr->sinkPorts()[0]->readPort();
		DUInt32 *n;
		if (!(n = dynamic_cast<DUInt32 *>(d))) {
			PERR("Failed to read port.");
		} else {
			_n.setValue(n->value());
		}
		delete d;
	}
}

void Worker::managerPostfire(IManagerActor *mgr)
{
	SimpleManagerActor *smgr;
	if ((smgr = dynamic_cast<SimpleManagerActor *>(mgr))) {
		DUInt32 *n = new DUInt32(_n);
		smgr->sourcePorts()[0]->writeChannel(n);
	}
}

void Worker::fire()
{
	PINF_1("Old value = " << _n.value());
	_n.setValue(_n.value() + 1);
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
