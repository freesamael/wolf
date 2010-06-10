/**
 * \file SimpleWorkerDispatcher.cpp
 * \date Jun 9, 2010
 * \author samael
 */

#include "SimpleWorkerDispatcher.h"

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
	return rsocks[_p++];
}

}