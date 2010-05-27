/**
 * \file ActorExecutor.cpp
 * \date May 26, 2010
 * \author samael
 */

#include "ActorExecutor.h"
#include "AbstractWorkerActor.h"

namespace wfe
{

/**
 * Keep running until dequeue() returns NULL.
 */
void ActorExecutor::run()
{
	AbstractWorkerActor *actor;
	while (actor = _parent->dequeue()) {
		actor->setup();
		do {
			actor->prefire();
			actor->fire();
			actor->postfire();
		} while (actor->testfire());
		actor->wrapup();
	}
	delete actor;
}

}
