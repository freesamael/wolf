/**
 * \file ManagerActor.cpp
 * \date Apr 13, 2010
 * \author samael
 */

#include "ManagerActor.h"
#include "RunnerAgent.h"

namespace wfe
{

AbstractActor::State ManagerActor::state()
{
	if (_state == NOT_READY) {
		bool ready = true;
		for (int i = 0; i < (int)sinkPorts().size(); i++)
			ready &= !sinkPorts()[i]->isEmpty();
		if (ready)
			_state = READY;
	}
	return _state;
}

void ManagerActor::fire()
{
	RunnerAgent::instance()->sendActor(_worker);
}

}