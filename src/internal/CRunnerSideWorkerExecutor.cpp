/**
 * \file CRunnerSideWorkerExecutor.cpp
 * \date May 26, 2010
 * \author samael
 */

#include "CRunnerSideWorkerExecutor.h"

#include <utility>
#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "AWorkerActor.h"

using namespace std;

namespace wolf
{

/**
 * Keep running until dequeue() returns NULL.
 */
void CRunnerSideWorkerExecutor::run()
{
	unsigned ecount = 0;
	while (!isDone()) {
		pair<uint32_t, AWorkerActor *> wp = _runner->takeWorker();
		AWorkerActor *worker;
		if ((worker = wp.second)) {
			worker->setup();
			do {
				worker->prefire();
				worker->fire();
				worker->postfire();
			} while (worker->testfire());
			worker->wrapup();
			_runner->sendWorkerFinished(wp.first, worker);
			ecount++;
		} else {
			usleep(10000);
		}
	}
	PINF_1(ecount << " workers executed.");
}

}
