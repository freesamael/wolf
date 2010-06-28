/**
 * \file SimpleManagerActor.h
 * \date Apr 13, 2010
 * \author samael
 */

#ifndef SIMPLEMANAGERACTOR_H_
#define SIMPLEMANAGERACTOR_H_

#include <iostream>
#include "HelperMacros.h"
#include "AbstractWorkerActor.h"
#include "Channel.h"
#include "IManagerActor.h"
#include "Mutex.h"

namespace wfe
{

/**
 * A simple implementation of IManagerActor.
 */
class SimpleManagerActor: public AbstractActor, public IManagerActor
{
public:
	SimpleManagerActor(AbstractWorkerActor *worker): _worker(worker),
		_state(NOT_READY), _statemx()
		{ _worker->managerInitialization(this); }
	~SimpleManagerActor() { _worker->managerFinalization(this);}
	inline void prefire()
		{ _state = RUNNING; _worker->managerPrefire(this); }
	inline void postfire()
		{ _state = FINISHED; _worker->managerPostfire(this); }
	void workerFinished(const AbstractWorkerActor &worker);
	State state();
	void fire();

private:
	SimpleManagerActor(const SimpleManagerActor &UNUSED(o)): AbstractActor(),
	IManagerActor(), _worker(), _state(NOT_READY), _statemx() {}
	SimpleManagerActor& operator=(const SimpleManagerActor &UNUSED(o))
		{ return *this; }
	AbstractWorkerActor *_worker;
	State _state;
	cml::Mutex _statemx;
};

}

#endif /* SIMPLEMANAGERACTOR_H_ */
