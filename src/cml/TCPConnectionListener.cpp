/**
 * \file TCPConnectionListener.cpp
 * \date Apr 27, 2010
 * \author samael
 */

#include <iostream>
#include <unistd.h>
#include "TCPConnectionListener.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * Major execution loop. If a padding socket was accepted, it notifies observers
 * and check for the next connection immediately. Otherwise, it sleeps for 50ms
 * before checking the next connection.
 */
void TCPConnectionListener::run()
{
	_done = false;
	_server->setNonblock(true);
	while (!_done) {
		TCPSocket *sock;
		if ((sock = _server->accept())) {
			PINFO("Got an incoming connection.");
			_mutex.lock();
			_ssock = sock;
			_mutex.unlock();
			notify();
		}
		usleep(sock ? 0 : 50000);
	}
}

}
