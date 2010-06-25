/**
 * \file ManagerActor.cpp
 * \date Apr 13, 2010
 * \author samael
 */

#include "ManagerActor.h"
#include "Master.h"

namespace wfe
{

AbstractActor::State ManagerActor::state()
{
	if (_state == NOT_READY) {
		bool ready = true;
		for (unsigned i = 0; i < sinkPorts().size(); i++)
			ready &= !sinkPorts()[i]->isEmpty();
		if (ready)
			_state = READY;
	}
	return _state;
}

void ManagerActor::fire()
{
	Master::instance()->runWorker(_worker, this);
}

void ManagerActor::workerFinished(const AbstractWorkerActor &worker)
{
#ifndef ENABLE_D2MCE /* Normal mode */
	PINF_2("Update worker.");
	_worker->update(worker);
#endif /* ENABLE_D2MCE */
	_state = POST_RUNNING;
}

}
