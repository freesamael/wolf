/**
 * \file ManagerActor.h
 * \date Apr 13, 2010
 * \author samael
 */

#ifndef MANAGERACTOR_H_
#define MANAGERACTOR_H_

#include <iostream>
#include "HelperMacros.h"
#include "WaitCondition.h"
#include "AbstractWorkerActor.h"
#include "Channel.h"

namespace wfe
{

class ManagerActor: public AbstractActor
{
public:
	ManagerActor(AbstractWorkerActor *worker): _worker(worker),
		_state(NOT_READY), _wait(), _muxwait()
		{ _worker->managerInitialization(this); }
	~ManagerActor() { _worker->managerFinalization(this);}

	inline void prefire() { _state = RUNNING; _worker->managerPrefire(this); }
	inline void postfire() { _state = FINISHED; _worker->managerPostfire(this); }

	/// Tell the manager actor that the worker sent has finished.
	void workerFinished(const AbstractWorkerActor &worker);
	State state();
	void fire();

private:
	ManagerActor(const ManagerActor &UNUSED(o)): _worker(), _state(NOT_READY),
	_wait(), _muxwait() {}
	ManagerActor& operator=(const ManagerActor &UNUSED(o)) { return *this; }
	AbstractWorkerActor *_worker;
	State _state;
	cml::WaitCondition _wait;
	cml::Mutex _muxwait;
};

}

#endif /* MANAGERACTOR_H_ */
