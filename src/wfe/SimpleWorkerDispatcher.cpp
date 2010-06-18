/**
 * \file SimpleWorkerDispatcher.cpp
 * \date Jun 9, 2010
 * \author samael
 */

#include <iostream>
#include "SimpleWorkerDispatcher.h"
#include "HelperMacros.h"

using namespace std;
using namespace cml;

namespace wfe {

unsigned SimpleWorkerDispatcher::_p = 0;

TCPSocket* SimpleWorkerDispatcher::choose(const vector<TCPSocket *> &rsocks)
{
	if (rsocks.size() == 0)
		return NULL;

	if (_p >= rsocks.size())
		_p = 0;
	PINF_2("Pick up runner " << _p);
	return rsocks[_p++];
}

}
