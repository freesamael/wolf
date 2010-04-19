/**
 * \file Counter.cpp
 * \date Apr 15, 2010
 * \author samael
 */

#include <cstdio>
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

#define TLV_TYPE_COUNTER	101

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

void Counter::managerPrefire(ManagerActor *manager)
{
	// Load memory.
	_mem = dynamic_cast<SharedMemory *>(sinkPorts()[0]->readPort());
	if (!_mem) {
		PERR("Invalid type.");
		return;
	}
	_mem->load();
	int *num = (int *)_mem->buffer();
	printf("%s: Num = %d %d %d %d\n", __PRETTY_FUNCTION__,
			num[0], num[1], num[2], num[3]);

	// Generate memory info.
	_meminfo = new TLVSharedMemoryInfo(_mem->name(), _mem->size());
	printf("%s: Meminfo: name = %s, size = %d\n", __PRETTY_FUNCTION__,
			_meminfo->name().c_str(), (int)_meminfo->size());
}

void Counter::managerPostfire(ManagerActor *manager)
{
	unsigned nodes = D2MCE::instance()->getNumberOfNodes();
	printf("%s: Barrier for %u nodes.\n", __PRETTY_FUNCTION__, nodes);
	D2MCE::instance()->barrier(nodes);
	printf("%s: Barrier passed.\n", __PRETTY_FUNCTION__);

	// Load memory.
	_mem->load();
	int *num = (int *)_mem->buffer();
	printf("%s: Num = %d %d %d %d\n", __PRETTY_FUNCTION__,
			num[0], num[1], num[2], num[3]);

	// Write port.
	sourcePorts()[0]->writeChannel(_mem);
}

void Counter::setup()
{
	_mem = D2MCE::instance()->createSharedMemory(_meminfo->name(), _meminfo->size());
}

void Counter::fire()
{
	int index = D2MCE::instance()->nodeId() - 1;
	if (index < 0) {
		PERR("Unexpected node id.");
		return;
	}

	_mem->lock();
	_mem->load();
	int *num = (int *)_mem->buffer();
	printf("%s: Num = %d %d %d %d\n", __PRETTY_FUNCTION__,
			num[0], num[1], num[2], num[3]);
	num[index]++;
	_mem->store();
	_mem->unlock();
}

void Counter::postfire()
{
	unsigned int nodes = D2MCE::instance()->getNumberOfNodes();
	printf("%s: Barrier for %u nodes.\n", __PRETTY_FUNCTION__, nodes);
	D2MCE::instance()->barrier(nodes);
	printf("%s: Barrier passed.\n", __PRETTY_FUNCTION__);
}

StandardTLVBlock* Counter::toTLVBlock() const
{
	StandardTLVBlock *infoblk = _meminfo->toTLVBlock();
	StandardTLVBlock *blk = new StandardTLVBlock(TLV_TYPE_COUNTER, infoblk->plainSize());
	memcpy(blk->value(), infoblk->plainBuffer(), blk->length());
	delete infoblk;
	return blk;
}
