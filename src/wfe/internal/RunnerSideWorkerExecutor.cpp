/**
 * \file RunnerSideWorkerExecutor.cpp
 * \date May 26, 2010
 * \author samael
 */

#include <utility>
#include "RunnerSideWorkerExecutor.h"
#include "AbstractWorkerActor.h"

using namespace std;

namespace wfe
{

/**
 * Keep running until dequeue() returns NULL.
 */
void RunnerSideWorkerExecutor::run()
{
	PINF_2("Worker executor starts.");
	unsigned ecount = 0;
	while (!isDone()) {
		pair<uint32_t, AbstractWorkerActor *> wp = _runner->takeWorker();
		AbstractWorkerActor *worker;
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
