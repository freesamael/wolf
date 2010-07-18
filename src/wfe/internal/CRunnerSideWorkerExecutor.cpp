/**
 * \file CRunnerSideWorkerExecutor.cpp
 * \date May 26, 2010
 * \author samael
 */

#include <utility>
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
}

}
