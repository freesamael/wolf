/**
 * \file SourcePort.h
 * \date Apr 12, 2010
 * \author samael
 */

#ifndef SOURCEPORT_H_
#define SOURCEPORT_H_

#include "IPort.h"
#include "IDrop.h"

namespace wfe
{

/**
 * Represents a output port.
 */
class SourcePort: public IPort
{
public:
	SourcePort(AbstractActor *owner, Channel *ch = NULL):
		_owner(owner), _channel(ch) {}
	SourcePort(const SourcePort &p):
		IPort(), _owner(p._owner), _channel(p._channel) {}
	SourcePort& operator=(const SourcePort &p)
		{ _owner = p._owner; _channel = p._channel; return *this; }
	inline Type type() const { return SOURCE; }
	inline AbstractActor* owner() const { return _owner; }
	inline Channel* channel() const { return _channel; }
	inline void setChannel(Channel *ch) { _channel = ch; }
	void writeChannel(IDrop *item);

private:
	AbstractActor *_owner;
	Channel *_channel;
};

}

#endif /* SOURCEPORT_H_ */
