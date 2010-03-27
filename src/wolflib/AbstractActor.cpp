/*
 * AbstractActor.cpp
 *
 *  Created on: Mar 22, 2010
 *      Author: samael
 */

#include "Port.h"
#include "Channel.h"
#include "AbstractActor.h"

namespace wfe
{

AbstractActor::~AbstractActor()
{
	for (int i = 0; i < (int)_inports.size(); i++)
		delete _inports[i];
	for (int i = 0; i < (int)_outports.size(); i++)
		delete _outports[i];
}

/**
 * @brief Attach a channel to a given port.
 */
bool AbstractActor::attachChannel(Port *port, Channel *channel)
{
	if (!port)
		return false;
	if (port->actor() != this)
		return false;
	port->setChannel(channel);
	return true;
}

AbstractActor::ActorState AbstractActor::state()
{
	if (_state == NOT_READY) {
		bool ready = true;
		for (int i = 0; i < (int)_inports.size(); i++)
			if (_inports[i]->channel()->state() != Channel::WRITTEN)
				ready = false;
		if (ready)
			_state = READY;
	}
	return _state;
}

}
