/**
 * \file CSimpleManagerActor.cpp
 * \date Apr 13, 2010
 * \author samael
 */

#include "CSimpleManagerActor.h"
#include "CMaster.h"

namespace wolf
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
#ifndef __D2MCE__ /* Normal mode */
	_worker->update(worker);
#endif /* __D2MCE__ */
	_statemx.lock();
	_state = POST_RUNNING;
	_statemx.unlock();
}

}
