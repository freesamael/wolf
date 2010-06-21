/**
 * \file Counter.cpp
 * \date Apr 15, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <cstring>
#include <SharedMemory.h>
#include <TLVObjectFactoryAutoRegistry.h>
#include <HelperMacros.h>
#include <D2MCE.h>
#include "Counter.h"
#include "CounterCreator.h"

using namespace std;
using namespace cml;
using namespace wfe;

#define TLV_TYPE_COUNTER	129

TLV_OBJECT_REGISTRATION(Counter, TLV_TYPE_COUNTER, CounterCreator);

Counter::Counter():
		_mem(NULL), _meminfo(NULL)
{
	addPort(IPort::SINK);
	addPort(IPort::SOURCE);
}

Counter::~Counter()
{
	delete sinkPorts()[0];
	delete sourcePorts()[0];
	delete _meminfo;
}

void Counter::managerPrefire(ManagerActor *UNUSED(manager))
{
	PINF_1("Manager Prefire");
	// Load memory.
	_mem = dynamic_cast<SharedMemory *>(sinkPorts()[0]->readPort());
	if (!_mem) {
		PERR("Invalid type.");
		return;
	}
	_mem->load();
	int *num = (int *)_mem->buffer();
	PINF_1("Num = " << num[0] << " " << num[1] << " " << num[2] << " " <<
			num[3]);

	// Generate memory info.
	_meminfo = new TLVSharedMemoryInfo(_mem->name(), _mem->size());
	PINF_1("Meminfo: name = " << _meminfo->name() << ", size = " <<
			_meminfo->size());
}

void Counter::managerPostfire(ManagerActor *UNUSED(manager))
{
	PINF_1("Manager Postfire");

	// Load memory.
	_mem->load();
	int *num = (int *)_mem->buffer();
	PINF_1("Num = " << num[0] << " " << num[1] << " " << num[2] << " " <<
			num[3]);

	// Write port.
	sourcePorts()[0]->writeChannel(_mem);
}

void Counter::setup()
{
	PINF_1("Setup");
	_mem = D2MCE::instance()->createSharedMemory(_meminfo->size(), _meminfo->name());
}

void Counter::fire()
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

void Counter::postfire()
{
	PINF_1("Postfire");
}

StandardTLVBlock* Counter::toTLVBlock() const
{
	StandardTLVBlock *infoblk = _meminfo->toTLVBlock();
	StandardTLVBlock *blk = new StandardTLVBlock(TLV_TYPE_COUNTER, infoblk->plainSize());
	memcpy(blk->value(), infoblk->plainBuffer(), blk->length());
	delete infoblk;
	return blk;
}
