/*
 * Channel.h
 *
 *  Created on: Mar 22, 2010
 *      Author: samael
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <string>
#include <SharedMemory.h>

namespace wfe
{

class AbstractActor;
class Channel
{
public:
	typedef enum ChannelState {
		EMPTY,
		WRITTEN
	} ChannelState;
	typedef enum IOType {
		INPUT,
		OUTPUT
	} IOType;

	Channel(const std::string &name): _name(name), _smem(NULL) {}
	inline ChannelState state() const { return (!_smem) ? EMPTY : WRITTEN; }
	inline const std::string& name() const { return _name; }
	inline cml::SharedMemory* read() { return _smem; }
	inline void write(cml::SharedMemory *mem) { _smem = mem; }

private:
	std::string _name;
	cml::SharedMemory *_smem;
};

}

#endif /* CHANNEL_H_ */
