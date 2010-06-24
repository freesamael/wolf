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
	_muxwait.lock();
	Master::instance()->runWorker(_worker, this);
	_wait.wait(&_muxwait);
	_muxwait.unlock();
}

void ManagerActor::workerFinished(const AbstractWorkerActor &worker)
{
#ifdef DISABLE_D2MCE	// In DSM mode the result is directly taken from DSM.
	PINF_2("Update worker.");
	_worker->update(worker);
#endif /* DISABLE_D2MCE */
	_wait.wakeOne();
	_state = POST_RUNNING;
}

}
