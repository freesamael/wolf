/**
 * \file CSimpleManagerActor.h
 * \date Apr 13, 2010
 * \author samael
 */

#ifndef CSIMPLEMANAGERACTOR_H_
#define CSIMPLEMANAGERACTOR_H_

#include <iostream>
#include "HelperMacros.h"
#include "AWorkerActor.h"
#include "CChannel.h"
#include "IManagerActor.h"
#include "CMutex.h"

namespace wolf
{

/**
 * A simple implementation of IManagerActor.
 */
class CSimpleManagerActor: public AActor, public IManagerActor
{
public:
	CSimpleManagerActor(AWorkerActor *worker): _worker(worker),
		_state(NOT_READY), _statemx()
		{ _worker->managerInitialization(this); }
	~CSimpleManagerActor() { _worker->managerFinalization(this);}
	inline void prefire()
		{ _state = RUNNING; _worker->managerPrefire(this); }
	inline void postfire()
		{ _state = FINISHED; _worker->managerPostfire(this); }
	void workerFinished(AWorkerActor *worker);
	State state();
	void fire();

private:
	CSimpleManagerActor(const CSimpleManagerActor &UNUSED(o)): AActor(),
	IManagerActor(), _worker(), _state(NOT_READY), _statemx() {}
	CSimpleManagerActor& operator=(const CSimpleManagerActor &UNUSED(o))
		{ return *this; }
	AWorkerActor *_worker;
	State _state;
	CMutex _statemx;
};

}

#endif /* CSIMPLEMANAGERACTOR_H_ */
