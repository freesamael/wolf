/**
 * \file Channel.cpp
 * \date Mar 22, 2010
 * \author samael
 */

#include "Channel.h"
#include "SinkPort.h"

using namespace std;

namespace wfe
{

/**
 * Attach a reader to the channel. It takes no effect if the port is already
 * attached.
 */
void Channel::attachReader(SinkPort *port)
{
	for (int i = 0; i < (int)_readers.size(); i++) {
		if (_readers[i] == port)
			return;
	}
	_readers.push_back(port);
}

/**
 * Detach a reader from the channel. It takes no effect if the port was not
 * attached before.
 */
void Channel::detachReader(SinkPort *port)
{
	vector<SinkPort *>::iterator iter;
	for (iter = _readers.begin(); iter != _readers.end(); iter++) {
		if (*iter == port) {
			_readers.erase(iter);
			return;
		}
	}
}

/**
 * Write an item to the channel, which dispatches the item to all the sink
 * ports attached. It's a thread-safe function protected by a pthread mutex
 * lock so that a series of write actions are guaranteed to have the same order
 * on all reader ports attached to this channel.
 */
void Channel::write(IDrop *item)
{
	pthread_mutex_lock(&_mutex);
	if (!_readers.empty()) {
		// Fit 1st ~ (N - 1)th reader.
		for (int i = 0; i < (int)_readers.size() - 1; i++) {
			_readers[i]->writePort(item->clone());
		}

		// Fit last reader.
		_readers[_readers.size() - 1]->writePort(item);
	}
	pthread_mutex_unlock(&_mutex);
}

}
