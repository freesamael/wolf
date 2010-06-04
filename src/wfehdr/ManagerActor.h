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
		_state(NOT_READY) { _worker->managerInitialization(this); }
	ManagerActor(const ManagerActor &mgr): _worker(mgr._worker),
		_state(NOT_READY) { _worker->managerInitialization(this); }
	~ManagerActor() { _worker->managerFinalization(this);}
	ManagerActor& operator=(const ManagerActor &UNUSED(mgr))
	{ PERR("You should not use assignment on ManagerActor."); return *this; }

	inline void prefire() { _state = RUNNING; _worker->managerPrefire(this); }
	inline void postfire() { _state = FINISHED; _worker->managerPostfire(this); }

	/// ManagerActor's wrapper for worker's ports.
	inline const std::vector<SinkPort *>& sinkPorts() const
		{ return _worker->sinkPorts(); }
	/// ManagerActor's wrapper for worker's ports.
	inline const std::vector<SourcePort *>& sourcePorts() const
		{ return _worker->sourcePorts(); }
	/// ManagerActor's wrapper for worker's ports.
	inline IPort* addPort(IPort::Type type) { return _worker->addPort(type); }
	/// ManagerActor's wrapper for worker's ports.
	inline void removePort(IPort *port) { _worker->removePort(port); }
	/// Tell the manager actor that the worker sent has finished.
	void workerFinished();
	State state();
	void fire();

private:
	AbstractWorkerActor *_worker;
	State _state;
	cml::WaitCondition _wait;
	cml::Mutex _muxwait;
};

}

#endif /* MANAGERACTOR_H_ */
