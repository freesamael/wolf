/**
 * \file MSortDataGenerator.cpp
 * \date Jun 28, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <stdint.h>
#include <CFlowVector.h>
#include <HelperMacros.h>
#include "MSortDataGenerator.h"

using namespace wolf;

MSortDataGenerator::MSortDataGenerator(int nports, int psize):
		_np(nports), _psize(psize), _state(READY)
{
	srand(time(NULL));
	for (int i = 0; i < _np; i++)
		addPort(IPort::SOURCE);
}

MSortDataGenerator::~MSortDataGenerator()
{
	while (!sourcePorts().empty())
		removePort(sourcePorts()[0]);
}

void MSortDataGenerator::fire()
{
	PINF_1("Generating data.");
	for (int i = 0; i < _np; i++) {
		CFlowVector<uint32_t> *d = new CFlowVector<uint32_t>();
		for (int j = 0; j < _psize; j++) {
			uint32_t n = (uint32_t)rand();
			d->push_back(n);
		}
		sourcePorts()[i]->writeChannel(d);
	}
	PINF_1("Data Generated.");
	_state = POST_RUNNING;
}
