/**
 * \file AlwaysFirstWorkerStealer.cpp
 * \date Jun 26, 2010
 * \author samael
 */

#include "AlwaysFirstWorkerStealer.h"

namespace wfe
{

void AlwaysFirstWorkerStealer::workerMissed()
{
	if (!isStealing()) {
		setStealing(true);
		if (_runner) {
			if (!_runner->runnerSocks().empty()) {
				_runner->sendWorkerSteal(_runner->runnerSocks()[0], _num);
			}
		}
		setStealing(false);
	}
}

}
