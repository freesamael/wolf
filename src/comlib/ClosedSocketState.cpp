/*
 * ClosedSocketState.cpp
 *
 *  Created on: Apr 5, 2010
 *      Author: samael
 */

#include <cstdio>
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "ClosedSocketState.h"
#include "SimpleActiveSocketState.h"
#include "TCPSocket.h"
#include "UDPSocket.h"

using namespace std;

namespace cml
{

ClosedSocketState *ClosedSocketState::_instance = NULL;

ClosedSocketState* ClosedSocketState::instance()
{
	if (!_instance)
		_instance = new ClosedSocketState();

	return _instance;
}

bool ClosedSocketState::activeOpen(AbstractSocket *sock,
		const HostAddress &addr, unsigned short port)
{
	if (open(sock))
		return sock->activeOpen(addr, port);
	return false;
}

bool ClosedSocketState::passiveOpen(AbstractSocket *sock,
		unsigned short port, int qlen)
{
	if (open(sock))
		return sock->passiveOpen(port, qlen);
	return false;
}

bool ClosedSocketState::open(AbstractSocket *sock)
{
	int type;
	int sockfd;

	// Check type.
	if (dynamic_cast<UDPSocket *>(sock))
		type = SOCK_DGRAM;
	else if (dynamic_cast<TCPSocket *>(sock))
		type = SOCK_STREAM;
	else {
		fprintf(stderr, "ClosedSocketState::open(): Error: Unsupported type.\n");
		return false;
	}

	// Initialize.
	if ((sockfd = socket(AF_INET, type, 0)) < 0) {
		perror("ClosedSocketState::open()");
		return false;
	}
	sock->setSockfd(sockfd);
	sock->changeState(SimpleActiveSocketState::instance());

	return true;
}

}
