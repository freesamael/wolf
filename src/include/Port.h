/*
 * Port.h
 *
 *  Created on: Mar 23, 2010
 *      Author: samael
 */

#ifndef PORT_H_
#define PORT_H_

#include <cstddef>
#include "IActor.h"

namespace wfe
{

class Channel;
class Port
{
public:
	Port(IActor *actor): _actor(actor), _channel(NULL) {}
	inline IActor* actor() const { return _actor; }
	inline Channel* channel() const { return _channel; }
	inline void setChannel(Channel *channel) { _channel = channel; }

private:
	IActor *_actor;
	Channel *_channel;
};

}

#endif /* PORT_H_ */
