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
	Channel(const std::string &name = ""):
		_name(name), _mutex(), _readers() { }
	~Channel() { }
	inline const std::string& name() const { return _name; }
	inline const std::vector<SinkPort *>& readers() { return _readers; }
	void attachReader(SinkPort *port);
	void detachReader(SinkPort *port);
	void write(IDrop *item);

private:
	std::string _name;
	cml::Mutex _mutex;
	std::vector<SinkPort *> _readers;
};

}

#endif /* CHANNEL_H_ */
