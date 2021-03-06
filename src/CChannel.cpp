/**
 * \file CChannel.cpp
 * \date Mar 22, 2010
 * \author samael
 */

#include "CChannel.h"
#include "CSinkPort.h"

using namespace std;

namespace wolf
{

/**
 * Attach a reader to the channel. It takes no effect if the port is already
 * attached.
 */
void CChannel::attachReader(CSinkPort *port)
{
	for (unsigned i = 0; i < _readers.size(); i++) {
		if (_readers[i] == port)
			return;
	}
	_readers.push_back(port);
	port->setChannel(this);
}

/**
 * Detach a reader from the channel. It takes no effect if the port was not
 * attached before.
 */
void CChannel::detachReader(CSinkPort *port)
{
	vector<CSinkPort *>::iterator iter;
	for (iter = _readers.begin(); iter != _readers.end(); ++iter) {
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
void CChannel::write(IDrop *item)
{
	_mutex.lock();
	if (!_readers.empty()) {
		// Fit 1st ~ (N - 1)th reader.
		for (unsigned i = 0; i < _readers.size() - 1; i++) {
			_readers[i]->writePort(item->clone());
		}

		// Fit last reader.
		_readers[_readers.size() - 1]->writePort(item);
	}
	_mutex.unlock();
}

}
