#ifndef PORT_H_
#define PORT_H_

#include <cstddef>
#include "IActor.h"
#include "Channel.h"

namespace wfe
{

class Port
{
public:
	typedef enum Type {
		INPUT,
		OUTPUT
	} Type;
	static const char *TypeString[];
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
