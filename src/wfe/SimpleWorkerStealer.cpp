/**
 * \file SimpleWorkerStealer.cpp
 * \date Jun 23, 2010
 * \author samael
 */

#include <ctime>
#include <cstdlib>
#include "WaitCondition.h"
#include "SimpleWorkerStealer.h"

using namespace std;
using namespace cml;

namespace wfe
{

SimpleWorkerStealer::SimpleWorkerStealer(int n):
		_runner(NULL), _mx(), _stealing(false), _num(n)
{
	srand(time(NULL));
}

void SimpleWorkerStealer::workerMissed()
{
	if (!isStealing()) {
		setStealing(true);
		if (!_runner) {
			PERR("No runner has been set.");
		} else {
			if (!_runner->runnerSocks().empty()) {
				int index = rand() % _runner->runnerSocks().size();
				_runner->sendWorkerSteal(_runner->runnerSocks()[index], 1);
			}
		}
		setStealing(false);
	}
}

}
