/**
 * \file CRunnerSideWorkerExecutor.cpp
 * \date May 26, 2010
 * \author samael
 */

#include <utility>
#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "CRunnerSideWorkerExecutor.h"
#include "AWorkerActor.h"

using namespace std;

namespace wfe
{

/**
 * Keep running until dequeue() returns NULL.
 */
void CRunnerSideWorkerExecutor::run()
{
	PINF_2("Worker executor starts.");
	unsigned ecount = 0;
	while (!isDone()) {
		pair<uint32_t, AWorkerActor *> wp = _runner->takeWorker();
		AWorkerActor *worker;
		if ((worker = wp.second)) {
			PINF_2("Executing a worker.");
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
	PINF_2("Worker executor ends. Totally " << ecount << " workers executed.");
}

}
