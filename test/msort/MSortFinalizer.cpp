/**
 * \file MSortFinalizer.cpp
 * \date Jun 28, 2010
 * \author samael
 */

#define __STDC_LIMIT_MACROS // Needed to use UINTx_MAX macros in <stdint.h>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <HelperMacros.h>
#include "MSortFinalizer.h"

using namespace std;
using namespace wfe;

MSortFinalizer::MSortFinalizer(int nports):
		_state(NOT_READY), _vex(), _its()
{
	for (int i = 0; i < nports; i++)
		addPort(IPort::SINK);
}

AbstractActor::State MSortFinalizer::state()
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

void MSortFinalizer::prefire()
{
	for (unsigned i = 0; i < sinkPorts().size(); i++) {
		DVector<uint32_t> *d;
		if (!(d = dynamic_cast<DVector<uint32_t> *>(sinkPorts()[i]->readPort()))) {
			PERR("Invalid object.");
		} else {
			_vex.push_back(d);
			_its.push_back(d->begin());
		}
	}
}

void MSortFinalizer::fire()
{
	while (!testend()) {
		cout << findmin() << endl;
	}
	_state = POST_RUNNING;
}

void MSortFinalizer::postfire()
{
	for (unsigned i = 0; i < _vex.size(); i++)
		delete _vex[i];
	_state = FINISHED;
}

bool MSortFinalizer::testend()
{
	bool end = true;
	for (unsigned i = 0; i < _vex.size(); i++)
		end &= _its[i] == _vex[i]->end();
	return end;
}

uint32_t MSortFinalizer::findmin()
{
	uint32_t min = UINT32_MAX;
	for (unsigned i = 0; i < _vex.size(); i++) {
		if (_its[i] != _vex[i]->end()) {
			if (*_its[i] < min)
				min = *_its[i]++;
		}
	}
	return min;
}
