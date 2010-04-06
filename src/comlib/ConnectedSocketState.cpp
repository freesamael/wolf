/*
 * ConnectedSocketState.cpp
 *
 *  Created on: Apr 5, 2010
 *      Author: samael
 */

#include <cstdio>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "ConnectedSocketState.h"
#include "ClosedSocketState.h"
#include "TCPSocket.h"

using namespace std;

namespace cml
{

ConnectedSocketState *ConnectedSocketState::_instance = NULL;

ConnectedSocketState* ConnectedSocketState::instance()
{
	if (!_instance)
		_instance = new ConnectedSocketState();
	return _instance;
}

bool ConnectedSocketState::close(AbstractSocket *sock)
{
	if (shutdown(sock->sockfd(), SHUT_RDWR) != 0) {
		perror("ConnectedSocketState::close(): shutdown");
		return false;
	}

	if (::close(sock->sockfd()) != 0) {
		perror("ConnectedSocketState::close(): close");
		return false;
	}

	sock->changeState(ClosedSocketState::instance());
	return true;
}

ssize_t ConnectedSocketState::read(AbstractSocket *sock, char *buf, size_t size)
{
	ssize_t result;
	if ((result = ::read(sock->sockfd(), buf, size)) < 0)
		perror("ConnectedSocketState::read()");
	return result;
}

ssize_t ConnectedSocketState::write(AbstractSocket *sock, const char *buf,
		size_t size)
{
	ssize_t result;
	if ((result = ::write(sock->sockfd(), buf, size)) < 0)
		perror("ConnectedSocketState::write()");
	return result;

}

}