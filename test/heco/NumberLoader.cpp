/**
 * \file NumberLoader.cpp
 * \date Apr 15, 2010
 * \author samael
 */

#include <cstdio>
#include <SharedMemory.h>
#include <HelperMacros.h>
#include "NumberLoader.h"

using namespace wfe;

AbstractActor::State NumberLoader::state()
{
	if (_state == NOT_READY) {
		bool ready = true;
		for (int i = 0; i < (int)sinkPorts().size(); i++)
			ready &= !sinkPorts()[i]->isEmpty();
		if (ready)
			_state = READY;
	}
	return _state;
}

void NumberLoader::fire()
{
	SharedMemory *mem;
	if (!(mem = dynamic_cast<SharedMemory *>(sinkPorts()[0]->readPort()))) {
		PERR("Invalid type.");
	}
	int *num = (int *)mem->buffer();
	printf("%s: Num = %d %d %d %d\n", __PRETTY_FUNCTION__,
			num[0], num[1], num[2], num[3]);
	_state = FINISHED;
}
