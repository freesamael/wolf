/**
 * \file HecoDSMFinalizer.cpp
 * \date Apr 15, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <CSharedMemory.h>
#include <HelperMacros.h>
#include "HecoDSMFinalizer.h"

using namespace wolf;

AActor::State HecoDSMFinalizer::state()
{
	if (_state == NOT_READY) {
		bool ready = true;
		for (unsigned i = 0; i < sinkPorts().size(); i++)
			ready &= !sinkPorts()[i]->isEmpty();
		if (ready)
			_state = READY;
	}
	return _state;
}

void HecoDSMFinalizer::fire()
{
	SharedMemory *mem;
	if (!(mem = dynamic_cast<SharedMemory *>(sinkPorts()[0]->readPort()))) {
		PERR("Invalid type.");
	}
	int *num = (int *)mem->buffer();
	PINF_1("Num = " << num[0] << " " << num[1] << " " <<  num[2] <<
			" " << num[3]);
	_state = POST_RUNNING;
}
