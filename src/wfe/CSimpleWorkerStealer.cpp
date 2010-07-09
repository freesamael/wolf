/**
 * \file CSimpleWorkerStealer.cpp
 * \date Jun 23, 2010
 * \author samael
 */

#include <ctime>
#include <cstdlib>
#include "CWaitCondition.h"
#include "CSimpleWorkerStealer.h"

using namespace std;
using namespace cml;

namespace wfe
{

CSimpleWorkerStealer::CSimpleWorkerStealer(int n):
		_runner(NULL), _mx(), _stealing(false), _num(n)
{
	srand(time(NULL));
}

void CSimpleWorkerStealer::workerMissed()
{
	if (!isStealing()) {
		setStealing(true);
		if (!_runner) {
			PERR("No runner has been set.");
		} else {
			if (!_runner->runnerSocks().empty()) {
				int index = rand() % _runner->runnerSocks().size();
				_runner->sendWorkerSteal(_runner->runnerSocks()[index], _num);
			}
		}
		setStealing(false);
	}
}

}
