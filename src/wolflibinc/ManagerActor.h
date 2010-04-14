/**
 * \file ManagerActor.h
 * \date Apr 13, 2010
 * \author samael
 */

#ifndef MANAGERACTOR_H_
#define MANAGERACTOR_H_

#include "AbstractActor.h"
#include "AbstractWorkerActor.h"

namespace wfe
{

class ManagerActor: public AbstractActor
{
public:
	ManagerActor(AbstractWorkerActor *worker):
		_worker(worker), _state(NOT_READY), _firecond(true) {}
	State state();
	inline void setup() { _worker->initialize(this); }
	inline void wrapup() { _worker->finalize(this); }
	inline bool testfire() { return _firecond; }
	void prefire();
	void fire();
	void postfire();
	void reset();
	SinkPort* addSinkPort();
	SourcePort* addSourcePort();
	inline const std::vector<SinkPort *>& sinkPorts()
			{ return _worker->sinkPorts(); }
	inline const std::vector<SourcePort *>& sourcePorts()
			{ return _worker->sourcePorts(); }

private:
	AbstractWorkerActor *_worker;
	State _state;
	bool _firecond;
};

}

#endif /* MANAGERACTOR_H_ */
