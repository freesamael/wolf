/**
 * \file CTcpConnectionListener.cpp
 * \date Apr 27, 2010
 * \author samael
 */

#include <unistd.h>
#include "CTcpConnectionListener.h"
#include "HelperMacros.h"

namespace wolf
{

/**
 * Major execution loop. If a padding socket was accepted, it notifies observers
 * and check for the next connection immediately. Otherwise, it sleeps for 50ms
 * before checking the next connection.
 */
void CTcpConnectionListener::run()
{
	_server->setBlockable(false);
	while (!isDone()) {
		CTcpSocket *sock;
		if ((sock = _server->accept())) {
			_mx.lock();
			_ssock = sock;
			_mx.unlock();
			notify();
		}
		usleep(sock ? 0 : 50000);
	}
}

}
