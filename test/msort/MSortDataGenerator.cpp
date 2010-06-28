/**
 * \file MSortDataGenerator.cpp
 * \date Jun 28, 2010
 * \author samael
 */

#include <cstdlib>
#include <ctime>
#include <stdint.h>
#include <DVector.h>
#include "MSortDataGenerator.h"

using namespace wfe;

MSortDataGenerator::MSortDataGenerator(int nports, int psize):
		_np(nports), _psize(psize)
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
	for (int i = 0; i < _np; i++) {
		DVector<uint32_t> *d = new DVector<uint32_t>();
		for (int j = 0; j < _psize; j++) {
			uint32_t n = (uint32_t)rand();
			d->push_back(n);
		}
		sourcePorts()[i]->writeChannel(d);
	}
	_state = POST_RUNNING;
}
