/**
 * \file MSortWorker.cpp
 * \date Jun 28, 2010
 * \author samael
 */

#define __STDC_LIMIT_MACROS // Needed to use UINTx_MAX macros in <stdint.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <stdint.h>
#include <arpa/inet.h>
#include <HelperMacros.h>
#include <SimpleManagerActor.h>
#include <TLVObjectFactoryAutoRegistry.h>
#include "MSortWorker.h"
#include "MSortWorkerCreator.h"

using namespace std;
using namespace cml;
using namespace wfe;

#define TLV_TYPE_WORKER	131
TLV_OBJECT_REGISTRATION(MSortWorker, TLV_TYPE_WORKER, MSortWorkerCreator);

MSortWorker::MSortWorker():
		_vec(), _mx()
{

}

void MSortWorker::managerInitialization(IManagerActor *mgr)
{
//	PINF_1("Initializing manager.");
	SimpleManagerActor *smgr;
	if (!(smgr = dynamic_cast<SimpleManagerActor *>(mgr))) {
		PERR("Invalid operation.");
	} else {
		smgr->addPort(IPort::SINK);
		smgr->addPort(IPort::SOURCE);
	}
}

void MSortWorker::managerFinalization(IManagerActor *mgr)
{
//	PINF_1("Finalizing manager.");
	SimpleManagerActor *smgr;
	if (!(smgr = dynamic_cast<SimpleManagerActor *>(mgr))) {
		PERR("Invalid operation.");
	} else {
		smgr->removePort(smgr->sinkPorts()[0]);
		smgr->removePort(smgr->sourcePorts()[0]);
	}
}

void MSortWorker::managerPrefire(wfe::IManagerActor *mgr)
{
	PINF_1("Manager prefire.");
	SimpleManagerActor *smgr;
	if (!(smgr = dynamic_cast<SimpleManagerActor *>(mgr))) {
		PERR("Invalid operation.");
	} else {
		DVector<uint32_t> *d;
		if (!(d = dynamic_cast<DVector<uint32_t> *>(smgr->sinkPorts()[0]->readPort()))) {
			PERR("Invalid object.");
		} else {
			_mx.lock();
			_vec = *d;
			_mx.unlock();
		}
		delete d;
	}
}

void MSortWorker::managerPostfire(wfe::IManagerActor *mgr)
{
	PINF_1("Manager postfire.");
	SimpleManagerActor *smgr;
	if (!(smgr = dynamic_cast<SimpleManagerActor *>(mgr))) {
		PERR("Invalid operation.");
	} else {
		DVector<uint32_t> *d = new DVector<uint32_t>();
		_mx.lock();
		*d = _vec;
		_mx.unlock();
		smgr->sourcePorts()[0]->writeChannel(d);
	}
}

void MSortWorker::update(const AbstractWorkerActor &o)
{
	PINF_1("Updating results.");
	const MSortWorker *w;
	if (!(w = dynamic_cast<const MSortWorker *>(&o))) {
		PERR("Invalid worker.");
	} else {
		_vec = w->_vec;
	}
}

void MSortWorker::fire()
{
	PINF_1("Sorting " << _vec.size() << " items.");
	for (int i = 1; i < (int)_vec.size(); i++) {
		uint32_t value = _vec[i];
		int j = i - 1;
		bool done = false;
		do {
			if (_vec[j] > value) {
				_vec[j + 1] = _vec[j];
				j--;
				if (j < 0)
					done = true;
			} else {
				done = true;
			}
		} while (!done);
		_vec[j + 1] = value;
	}
}

void MSortWorker::setVector(const DVector<uint32_t> &v)
{
	_vec = v;
}

cml::StandardTLVBlock* MSortWorker::toTLVBlock() const
{
	if ((_vec.size() * sizeof(uint32_t) + ITLVBlock::szHeader) > UINT16_MAX) {
		PERR("Too large to be a TLV object.");
		return NULL;
	}

	StandardTLVBlock *blk = new StandardTLVBlock(TLV_TYPE_WORKER,
			_vec.size() * sizeof(uint32_t));
	for (unsigned i = 0; i < _vec.size(); i++) {
		uint32_t nbytes = htonl(_vec[i]);
		memcpy(blk->value() + i * sizeof(uint32_t), &nbytes,
				sizeof(uint32_t));
	}

	return blk;
}
