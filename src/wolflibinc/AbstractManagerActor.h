/*
 * AbstractManagerActor.h
 *
 *  Created on: Mar 28, 2010
 *      Author: samael
 */

#ifndef ABSTRACTMANAGERACTOR_H_
#define ABSTRACTMANAGERACTOR_H_

#include "IActor.h"
#include "ISinkComponent.h"
#include "ISourceComponent.h"
#include "IManagerWorkerExecutor.h"
#include "AbstractWorkerActor.h"

namespace wfe
{

class AbstractManagerActor: public IActor, public ISinkComponent,
		public ISourceComponent
{
public:
	AbstractManagerActor(IManagerWorkerExecutor *exec = NULL):
		_exec(exec), _state(IActor::NOT_READY) {}
	virtual ~AbstractManagerActor();
	virtual void fire();
	bool isInputReady() const;
	inline const std::vector<Port *>& inports() { return _inports; }
	inline const std::vector<Port *>& outports() { return _outports; }
	inline const std::vector<AbstractWorkerActor *>& workers() { return _workers; }

protected:
	IManagerWorkerExecutor *_exec;
	IActor::State _state;
	std::vector<Port *> _inports;
	std::vector<Port *> _outports;
	std::vector<AbstractWorkerActor *> _workers;
};

}

#endif /* ABSTRACTMANAGERACTOR_H_ */
