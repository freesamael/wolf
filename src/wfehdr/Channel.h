/**
 * \file Channel.h
 * \date Mar 22, 2010
 * \author samael
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <string>
#include <vector>
#include <pthread.h>
#include "IDrop.h"

namespace wfe
{

class SinkPort;
class Channel
{
public:
	Channel(const std::string &name = ""):
		_name(name), _mutex(), _readers() { pthread_mutex_init(&_mutex, NULL); }
	~Channel() { pthread_mutex_destroy(&_mutex); }
	inline const std::string& name() const { return _name; }
	inline const std::vector<SinkPort *>& readers() { return _readers; }
	void attachReader(SinkPort *port);
	void detachReader(SinkPort *port);
	void write(IDrop *item);

private:
	std::string _name;
	pthread_mutex_t _mutex;
	std::vector<SinkPort *> _readers;
};

}

#endif /* CHANNEL_H_ */
