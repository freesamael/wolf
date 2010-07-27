/**
 * \file CSourcePort.h
 * \date Apr 12, 2010
 * \author samael
 */

#ifndef CSOURCEPORT_H_
#define CSOURCEPORT_H_

#include "IPort.h"
#include "IDrop.h"

namespace wolf
{

/**
 * Represents a output port.
 */
class CSourcePort: public IPort
{
public:
	CSourcePort(AActor *owner, CChannel *ch = NULL):
		_owner(owner), _channel(ch) {}
	CSourcePort(const CSourcePort &p):
		IPort(), _owner(p._owner), _channel(p._channel) {}
	CSourcePort& operator=(const CSourcePort &p)
		{ _owner = p._owner; _channel = p._channel; return *this; }
	inline Type type() const { return SOURCE; }
	inline AActor* owner() const { return _owner; }
	inline CChannel* channel() const { return _channel; }
	inline void setChannel(CChannel *ch) { _channel = ch; }
	void writeChannel(IDrop *item);

private:
	AActor *_owner;
	CChannel *_channel;
};

}

#endif /* CSOURCEPORT_H_ */
