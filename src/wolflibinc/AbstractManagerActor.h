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

namespace wfe
{

class AbstractManagerActor: public IActor, public ISinkComponent,
		public ISourceComponent
{
public:
	AbstractManagerActor(): _state(IActor::NOT_READY) {}
	virtual ~AbstractManagerActor();
	bool isInputReady() const;
	inline const std::vector<Port *>& inports() { return _inports; }
	inline const std::vector<Port *>& outports() { return _outports; }

protected:
	IActor::State _state;
	std::vector<Port *> _inports;
	std::vector<Port *> _outports;
};

}

#endif /* ABSTRACTMANAGERACTOR_H_ */
