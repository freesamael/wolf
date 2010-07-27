/**
 * \file CSinkPort.h
 * \date Apr 12, 2010
 * \author samael
 */

#ifndef CSINKPORT_H_
#define CSINKPORT_H_

#include <deque>
#include "IPort.h"
#include "IDrop.h"

namespace wolf
{

/**
 * Represents a input port.
 */
class CSinkPort: public IPort
{
public:
	CSinkPort(AActor *owner, CChannel *ch = NULL):
		_owner(owner), _channel(ch), _queue() {}
	CSinkPort(const CSinkPort &p):
		IPort(), _owner(p._owner), _channel(p._channel), _queue() {}
	CSinkPort& operator=(const CSinkPort &p)
		{ _owner = p._owner; _channel = p._channel; return *this; }
	inline Type type() const { return SINK; }
	inline AActor* owner() const { return _owner; }
	inline CChannel* channel() const { return _channel; }
	inline bool isEmpty() const { return _queue.empty(); }
	void setChannel(CChannel *ch);
	void writePort(IDrop *item);
	IDrop* readPort();

private:
	AActor *_owner;
	CChannel *_channel;
	std::deque<IDrop *> _queue;
};

}

#endif /* CSINKPORT_H_ */
