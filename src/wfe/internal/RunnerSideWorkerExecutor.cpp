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
	while (!isDone()) {
		pair<uint32_t, AbstractWorkerActor *> wp = _runner->takeWorker();
		AbstractWorkerActor *worker;
		if ((worker = wp.second)) {
			worker->setup();
			do {
				worker->prefire();
				worker->fire();
				worker->postfire();
			} while (worker->testfire());
			worker->wrapup();
			_runner->workerFinished(wp.first, worker);
		} else {
			usleep(10000);
		}
	}
}

}
