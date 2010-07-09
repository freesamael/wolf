/**
 * \file CSimpleWorkerDispatcher.cpp
 * \date Jun 9, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "CSimpleWorkerDispatcher.h"
#include "HelperMacros.h"

using namespace std;
using namespace cml;

namespace wfe {

unsigned CSimpleWorkerDispatcher::_p = 0;

CTcpSocket* CSimpleWorkerDispatcher::choose(const vector<CTcpSocket *> &rsocks)
{
	if (rsocks.size() == 0)
		return NULL;

	if (_p >= rsocks.size())
		_p = 0;
	PINF_2("Pick up runner " << _p);
	return rsocks[_p++];
}

}
