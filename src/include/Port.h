/*
 * Port.h
 *
 *  Created on: Mar 23, 2010
 *      Author: samael
 */

#ifndef PORT_H_
#define PORT_H_

#include <cstddef>

namespace wfe
{

class AbstractActor;
class Channel;
class Port
{
public:
	Port(AbstractActor *actor): _actor(actor), _channel(NULL) {}
	inline AbstractActor* actor() const { return _actor; }
	inline Channel* channel() const { return _channel; }
	inline void setChannel(Channel *channel) { _channel = channel; }

private:
	AbstractActor *_actor;
	Channel *_channel;
};

}

#endif /* PORT_H_ */
