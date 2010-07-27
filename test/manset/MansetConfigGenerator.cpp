/**
 * \file MansetConfigGenerator.cpp
 * \date Jul 18, 2010
 * \author samael
 */

#include <CFlowUint32.h>
#include "MansetConfigGenerator.h"
#include "MansetException.h"

using namespace wolf;

MansetConfigGenerator::MansetConfigGenerator(uint32_t imgwidth,
		uint32_t imgheight, uint32_t rows):
		_state(READY), _imgwidth(imgwidth), _imgheight(imgheight),
		_rows(rows), _nports(0)
{
	if (_imgheight % _rows != 0)
		throw MansetException("Must divide exactly.");

	_nports = _imgheight / _rows;
	for (unsigned i = 0; i < _nports; i++)
		addPort(IPort::SOURCE);
}

MansetConfigGenerator::~MansetConfigGenerator()
{
	for (unsigned i = 0; i < _nports; i++)
		removePort(sourcePorts()[0]);
}

void MansetConfigGenerator::fire()
{
	for (unsigned i = 0; i < _nports; i++) {
		sourcePorts()[i]->writeChannel(new CFlowUint32(_imgwidth));	// imgwidth.
		sourcePorts()[i]->writeChannel(new CFlowUint32(_imgheight));// imgheight.
		sourcePorts()[i]->writeChannel(new CFlowUint32(i * _rows));	// current row.
		sourcePorts()[i]->writeChannel(new CFlowUint32(_rows));		// rows.
	}
	_state = POST_RUNNING;
}
