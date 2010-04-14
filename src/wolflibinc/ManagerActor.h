/**
 * \file ManagerActor.h
 * \date Apr 13, 2010
 * \author samael
 */

#ifndef MANAGERACTOR_H_
#define MANAGERACTOR_H_

#include "AbstractWorkerActor.h"

namespace wfe
{

class ManagerActor: public AbstractActor
{
public:
	ManagerActor(AbstractWorkerActor *worker):
		_worker(worker), _state(NOT_READY) { _worker->initializeManager(this); }
	~ManagerActor() { _worker->finalizeManager(this);}
	inline void setup() { _worker->setupManager(this); _state = RUNNING; }
	inline void wrapup() { _worker->wrapupManager(this); _state = FINISHED; }
	State state();
	void fire();

private:
	AbstractWorkerActor *_worker;
	State _state;
};

}

#endif /* MANAGERACTOR_H_ */
