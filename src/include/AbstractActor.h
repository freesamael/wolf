/*
 * AbstractActor.h
 *
 *  Created on: Mar 22, 2010
 *      Author: samael
 */

#ifndef ABSTRACTACTOR_H_
#define ABSTRACTACTOR_H_

#include <vector>

namespace wfe
{

class Port;
class Channel;
class AbstractActor
{
public:
	typedef enum ActorState {
		NOT_READY,
		READY,
		RUNNING,
		FINISH
	} ActorState;
	AbstractActor(): _state(NOT_READY) {}
	virtual ~AbstractActor();
	inline const std::vector<Port*>& inputPorts() const { return _inports; }
	inline const std::vector<Port*>& outputPorts() const { return _outports; }
	bool attachChannel(Port *port, Channel *channel);
	virtual ActorState state();
	virtual void preFire() { _state = RUNNING; }
	virtual void fire() = 0;
	virtual void postFire() { _state = FINISH; }
	virtual void reset() { _state = NOT_READY; }

protected:
	ActorState _state;
	std::vector<Port*> _inports;
	std::vector<Port*> _outports;
};

}

#endif /* ABSTRACTACTOR_H_ */
