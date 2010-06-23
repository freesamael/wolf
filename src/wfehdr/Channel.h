/**
 * \file Channel.h
 * \date Mar 22, 2010
 * \author samael
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <string>
#include <vector>
#include "Mutex.h"
#include "IDrop.h"

namespace wfe
{

class SinkPort;
class Channel
{
public:
	Channel(): _mutex(), _readers() { }
	~Channel() { }
	inline const std::vector<SinkPort *>& readers() { return _readers; }
	void attachReader(SinkPort *port);
	void detachReader(SinkPort *port);
	void write(IDrop *item);

private:
	cml::Mutex _mutex;
	std::vector<SinkPort *> _readers;
};

}

#endif /* CHANNEL_H_ */
