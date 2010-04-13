/**
 * \file ManagerActor.h
 * \date Apr 13, 2010
 * \author samael
 */

#ifndef MANAGERACTOR_H_
#define MANAGERACTOR_H_

#include "IActor.h"
#include "ISinkComponent.h"
#include "ISourceComponent.h"
#include "IWorkerActor.h"

namespace wfe
{

class ManagerActor: public IActor, public ISinkComponent,
		public ISourceComponent
{
public:
	ManagerActor(IWorkerActor *worker);
	~ManagerActor();
	State state();
	void setup();
	void wrapup();
	bool testfire();
	void prefire();
	void fire();
	void postfire();
	void reset();
	SinkPort* addSinkPort();
	SourcePort* addSourcePort();
	inline const std::vector<SinkPort *>& sinkPorts() { return _sinp; }
	inline const std::vector<SourcePort *>& sourcePorts() { return _srcp; }

private:
	IWorkerActor *_worker;
	std::vector<SinkPort *> _sinp;
	std::vector<SourcePort *> _srcp;
	bool _firecond;
};

}

#endif /* MANAGERACTOR_H_ */
