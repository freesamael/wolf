/**
 * \file CSinkPort.cpp
 * \date Apr 12, 2010
 * \author samael
 */

#include "CSinkPort.h"
#include "CChannel.h"

namespace wolf
{

/**
 * Write an item into the port. It's used by the channel attached.
 */
void CSinkPort::writePort(IDrop *item)
{
	_queue.push_back(item);
}

/**
 * Read an item from the port. It's used by the actor who owns the port.
 *
 * \return
 * The first item of the port queue, or NULL if the queue is empty.
 */
IDrop* CSinkPort::readPort()
{
	IDrop *item = NULL;
	if (!_queue.empty()) {
		item = _queue.front();
		_queue.pop_front();
	}
	return item;
}

void CSinkPort::setChannel(CChannel *ch)
{
	if (_channel != ch) {
		_channel = ch;
		_channel->attachReader(this);
	}
}

}
