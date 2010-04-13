/**
 * \file SinkPort.cpp
 * \date Apr 12, 2010
 * \author samael
 */

#include "SinkPort.h"

namespace wfe
{

/**
 * Write an item into the port. It's used by the channel attached.
 */
void SinkPort::writePort(IDrop *item)
{
	_queue.push_back(item);
}

/**
 * Read an item from the port. It's used by the actor who owns the port.
 *
 * \return
 * The first item of the port queue, or NULL if the queue is empty.
 */
IDrop* SinkPort::readPort()
{
	IDrop *item = NULL;
	if (!_queue.empty()) {
		item = _queue.front();
		_queue.pop_front();
	}
	return item;
}

}
