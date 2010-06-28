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
		PINF_2("Try to steal " << _num << " workers.");
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
