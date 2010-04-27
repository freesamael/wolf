/**
 * \file TCPConnectionAcceptor.cpp
 * \date Apr 27, 2010
 * \author samael
 */

#include <unistd.h>
#include "TCPConnectionAcceptor.h"

namespace cml
{

/**
 * Major execution loop. If a padding socket was accepted, it notifies observers
 * and check for the next connection immediately. Otherwise, it sleeps for 50ms
 * before checking the next connection.
 */
void TCPConnectionAcceptor::run()
{
	_done = false;
	_server->setNonblock(true);
	while (!_done) {
		TCPSocket *sock;
		if ((sock = _server->accept())) {
			_ssock = sock;
			notify();
		}
		usleep(sock ? 0 : 50000);
	}
}

/**
 * Assignment.
 */
TCPConnectionAcceptor& TCPConnectionAcceptor::operator=(const TCPConnectionAcceptor &o)
{
	AbstractObservable::operator=(o);
	_server = o._server;
	_done = o._done;
	_ssock = o._ssock;
	return *this;
}

}
