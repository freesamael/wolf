/**
 * \file SinkPort.h
 * \date Apr 12, 2010
 * \author samael
 */

#ifndef SINKPORT_H_
#define SINKPORT_H_

#include <deque>
#include "IPort.h"
#include "IDrop.h"

namespace wfe
{

/**
 * Represents a input port.
 */
class SinkPort: public IPort
{
public:
	SinkPort(AbstractActor *owner, Channel *ch = NULL):
		_owner(owner), _channel(ch), _queue() {}
	SinkPort(const SinkPort &p):
		IPort(), _owner(p._owner), _channel(p._channel), _queue() {}
	SinkPort& operator=(const SinkPort &p)
		{ _owner = p._owner; _channel = p._channel; return *this; }
	inline Type type() const { return SINK; }
	inline AbstractActor* owner() const { return _owner; }
	inline Channel* channel() const { return _channel; }
	inline bool isEmpty() const { return _queue.empty(); }
	void setChannel(Channel *ch);
	void writePort(IDrop *item);
	IDrop* readPort();

private:
	AbstractActor *_owner;
	Channel *_channel;
	std::deque<IDrop *> _queue;
};

}

#endif /* SINKPORT_H_ */
