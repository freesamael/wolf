/**
 * \file HecoDSMWorker.cpp
 * \date Apr 15, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <cstring>
#include <CSharedMemory.h>
#include <CTlvObjectFactoryAutoRegistry.h>
#include <HelperMacros.h>
#include <CD2mce.h>
#include <IManagerActor.h>
#include <CSimpleManagerActor.h>
#include "HecoDSMWorker.h"
#include "HecoDSMWorkerCreator.h"

using namespace std;
using namespace cml;
using namespace wfe;

#define TLV_TYPE_WORKER	130
TLV_OBJECT_REGISTRATION(HecoDSMWorker, TLV_TYPE_WORKER, HecoDSMWorkerCreator);

HecoDSMWorker::HecoDSMWorker():
		_mem(NULL), _meminfo(NULL)
{
}

HecoDSMWorker::~HecoDSMWorker()
{
	delete _meminfo;
}

void HecoDSMWorker::managerInitialization(IManagerActor *mgr)
{
	CSimpleManagerActor *smgr;
	if ((smgr = dynamic_cast<CSimpleManagerActor *>(mgr))) {
		smgr->addPort(IPort::SINK);
		smgr->addPort(IPort::SOURCE);
	}
}

void HecoDSMWorker::managerFinalization(IManagerActor *mgr)
{
	CSimpleManagerActor *smgr;
	if ((smgr = dynamic_cast<CSimpleManagerActor *>(mgr))) {
		smgr->removePort(smgr->sinkPorts()[0]);
		smgr->removePort(smgr->sourcePorts()[0]);
	}
}

void HecoDSMWorker::managerPrefire(IManagerActor *mgr)
{
	CSimpleManagerActor *smgr;
	if ((smgr = dynamic_cast<CSimpleManagerActor *>(mgr))) {
		PINF_1("Manager Prefire");
		// Load memory.
		_mem = dynamic_cast<SharedMemory *>(smgr->sinkPorts()[0]->readPort());
		if (!_mem) {
			PERR("Invalid type.");
			return;
		}
		_mem->load();
		int *num = (int *)_mem->buffer();
		PINF_1("Num = " << num[0] << " " << num[1] << " " << num[2] << " " <<
				num[3]);

		// Generate memory info.
		_meminfo = new CTlvSharedMemoryInfo(_mem->name(), _mem->size());
		PINF_1("Meminfo: name = " << _meminfo->name() << ", size = " <<
				_meminfo->size());
	}
}

void HecoDSMWorker::managerPostfire(IManagerActor *mgr)
{
	CSimpleManagerActor *smgr;
	if ((smgr = dynamic_cast<CSimpleManagerActor *>(mgr))) {
		PINF_1("Manager Postfire");

		// Load memory.
		_mem->load();
		int *num = (int *)_mem->buffer();
		PINF_1("Num = " << num[0] << " " << num[1] << " " << num[2] << " " <<
				num[3]);

		// Write port.
		smgr->sourcePorts()[0]->writeChannel(_mem);
	}
}

void HecoDSMWorker::setup()
{
	PINF_1("Setup");
	_mem = D2MCE::instance()->createSharedMemory(_meminfo->size(), _meminfo->name());
}

void HecoDSMWorker::fire()
{
	PINF_1("Fire");
	int index = D2MCE::instance()->nodeId() - 1;
	if (index < 0) {
		PERR("Unexpected node id.");
		return;
	}

	_mem->lock();
	_mem->load();
	int *num = (int *)_mem->buffer();
	PINF_1("Num = " << num[0] << " " << num[1] << " " << num[2] << " " <<
			num[3]);
	num[index]++;
	PINF_1("Num = " << num[0] << " " << num[1] << " " << num[2] << " " <<
			num[3]);
	_mem->store();
	_mem->unlock();
}

void HecoDSMWorker::postfire()
{
	PINF_1("Postfire");
}

CTlvBlock* HecoDSMWorker::toTLVBlock() const
{
	CTlvBlock *infoblk = _meminfo->toTLVBlock();
	CTlvBlock *blk = new CTlvBlock(TLV_TYPE_WORKER, infoblk->plainSize());
	memcpy(blk->value(), infoblk->plainBuffer(), blk->length());
	delete infoblk;
	return blk;
}
