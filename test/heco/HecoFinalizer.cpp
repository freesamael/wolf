/**
 * \file HecoFinalizer.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <iostream>
#include <DUInt32.h>
#include "HecoFinalizer.h"

using namespace std;
using namespace wfe;

HecoFinalizer::HecoFinalizer(unsigned np):
		_state(NOT_READY)
{
	for (unsigned i = 0; i < np; i++)
		addPort(wfe::IPort::SINK);
}

HecoFinalizer::~HecoFinalizer()
{
	for (unsigned i = 0; i < sinkPorts().size(); i++)
		delete sinkPorts()[i];
}

AbstractActor::State HecoFinalizer::state()
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

void HecoFinalizer::fire()
{
	for (unsigned i = 0; i < sinkPorts().size(); i++) {
		IDrop *d = sinkPorts()[i]->readPort();
		DUInt32 *u32;
		if ((u32 = dynamic_cast<DUInt32 *>(d))) {
			cout << u32->value() << " ";
		}
		delete d;
	}
	cout << endl;
	_state = POST_RUNNING;
}
