/**
 * \file Channel.h
 * \date Mar 22, 2010
 * \author samael
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <vector>
#include <pthread.h>
#include "IDrop.h"

namespace wfe
{

class SinkPort;
class Channel
{
public:
	Channel() { pthread_mutex_init(&_mutex, NULL); }
	~Channel() { pthread_mutex_destroy(&_mutex); }
	inline const std::vector<SinkPort *>& readers() { return _readers; }
	void attachReader(SinkPort *port);
	void detachReader(SinkPort *port);
	void write(IDrop *item);

private:
	pthread_mutex_t _mutex;
	std::vector<SinkPort *> _readers;
};

}

#endif /* CHANNEL_H_ */
