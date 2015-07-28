/**
 * \file CAlwaysFirstWorkerStealer.cpp
 * \date Jun 26, 2010
 * \author samael
 */

#include "CAlwaysFirstWorkerStealer.h"

#include <iostream>
#include <sstream>

namespace wolf
{

void CAlwaysFirstWorkerStealer::workerMissed()
{
	if (!isStealing()) {
		setStealing(true);
		if (!_runner) {
			PERR("No runner has been set.");
		} else {
			if (!(_runner->runnerSocks().empty() || _runner->id() == 0)) {
				_runner->sendWorkerSteal(_runner->runnerSocks()[0], _num);
			}
		}
		setStealing(false);
	}
}

}
