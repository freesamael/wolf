/**
 * \file SinkPort.h
 * \date Apr 12, 2010
 * \author samael
 */

#ifndef SINKPORT_H_
#define SINKPORT_H_

#include <deque>
#include <pthread.h>
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
		_owner(owner), _channel(ch) {}
	inline Type type() const { return SINK; }
	inline AbstractActor* owner() const { return _owner; }
	inline Channel* channel() const { return _channel; }
	inline void setChannel(Channel *ch) { _channel = ch; }
	inline bool isEmpty() const { return _queue.empty(); }
	void writePort(IDrop *item);
	IDrop* readPort();

private:
	AbstractActor *_owner;
	Channel *_channel;
	std::deque<IDrop *> _queue;
	pthread_mutex_t _mutex;
};

}

#endif /* SINKPORT_H_ */
