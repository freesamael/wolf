/**
 * \file CSimpleManagerActor.cpp
 * \date Apr 13, 2010
 * \author samael
 */

#include "CSimpleManagerActor.h"
#include "CMaster.h"

namespace wfe
{

AActor::State CSimpleManagerActor::state()
{
	_statemx.lock();
	if (_state == NOT_READY) {
		bool ready = true;
		for (unsigned i = 0; i < sinkPorts().size(); i++)
			ready &= !sinkPorts()[i]->isEmpty();
		if (ready)
			_state = READY;
	}
	State s = _state;
	_statemx.unlock();

	return s;
}

void CSimpleManagerActor::fire()
{
	CMaster::instance()->runWorker(_worker, this);
}

void CSimpleManagerActor::workerFinished(AWorkerActor *worker)
{
#ifndef ENABLE_D2MCE /* Normal mode */
	PINF_2("Update worker.");
	_worker->update(worker);
#endif /* ENABLE_D2MCE */
	_statemx.lock();
	_state = POST_RUNNING;
	_statemx.unlock();
}

}
