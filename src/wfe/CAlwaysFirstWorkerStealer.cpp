/**
 * \file CAlwaysFirstWorkerStealer.cpp
 * \date Jun 26, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "CAlwaysFirstWorkerStealer.h"

namespace wfe
{

void CAlwaysFirstWorkerStealer::workerMissed()
{
	if (!isStealing()) {
		setStealing(true);
		if (!_runner) {
			PERR("No runner has been set.");
		} else {
			if (!(_runner->runnerSocks().empty() || _runner->id() == 0)) {
				PINF_2("Try to steal " << _num << " workers.");
				_runner->sendWorkerSteal(_runner->runnerSocks()[0], _num);
			}
		}
		setStealing(false);
	}
}

}
