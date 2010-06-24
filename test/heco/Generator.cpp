/**
 * \file Generator.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <DUInt32.h>
#include "Generator.h"

using namespace wfe;

Generator::Generator(unsigned np):
		_state(READY)
{
	for (unsigned i = 0; i < np; i++)
		addPort(IPort::SOURCE);
}

Generator::~Generator()
{
	for (unsigned i = 0; i < sourcePorts().size(); i++)
		delete sourcePorts()[i];
}

void Generator::fire()
{
	for (unsigned i = 0; i < sourcePorts().size(); i++) {
		DUInt32 *n = new DUInt32(0);
		sourcePorts()[i]->writeChannel(n);
	}
	_state = POST_RUNNING;
}
