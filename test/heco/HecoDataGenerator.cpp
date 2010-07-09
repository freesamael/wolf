/**
 * \file HecoDataGenerator.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <CFlowUint32.h>
#include "HecoDataGenerator.h"

using namespace wfe;

HecoDataGenerator::HecoDataGenerator(unsigned np):
		_state(READY)
{
	for (unsigned i = 0; i < np; i++)
		addPort(IPort::SOURCE);
}

HecoDataGenerator::~HecoDataGenerator()
{
	for (unsigned i = 0; i < sourcePorts().size(); i++)
		delete sourcePorts()[i];
}

void HecoDataGenerator::fire()
{
	for (unsigned i = 0; i < sourcePorts().size(); i++) {
		CFlowUint32 *n = new CFlowUint32(0);
		sourcePorts()[i]->writeChannel(n);
	}
	_state = POST_RUNNING;
}
