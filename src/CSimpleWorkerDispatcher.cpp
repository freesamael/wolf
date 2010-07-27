/**
 * \file CSimpleWorkerDispatcher.cpp
 * \date Jun 9, 2010
 * \author samael
 */

#include "CSimpleWorkerDispatcher.h"

using namespace std;
using namespace wolf;

namespace wolf {

unsigned CSimpleWorkerDispatcher::_p = 0;

CTcpSocket* CSimpleWorkerDispatcher::choose(const vector<CTcpSocket *> &rsocks)
{
	if (rsocks.size() == 0)
		return NULL;

	if (_p >= rsocks.size())
		_p = 0;
	return rsocks[_p++];
}

}
