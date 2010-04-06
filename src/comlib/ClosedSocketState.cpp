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
#include "ConnectedSocketState.h"
#include "BoundSocketState.h"
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
	if (!_initialize(sock))
		return false;

	// Clear and set address/port.
	sockaddr_in inaddr;
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = addr.toInetAddr();
	inaddr.sin_port = htons(port);

	// Perform connection.
	if (connect(sock->sockfd(), (struct sockaddr *)&inaddr, sizeof(inaddr)) != 0) {
		perror("ClosedSocketState::activeOpen()");
		return false;
	}

	sock->changeState(ConnectedSocketState::instance());
	return true;
}

bool ClosedSocketState::passiveOpen(AbstractSocket *sock,
		unsigned short port, int qlen)
{
	if (!_initialize(sock))
		return false;

	// Clear and set inet address/port.
	sockaddr_in inaddr;
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = INADDR_ANY;
	inaddr.sin_port = htons(port);

	// Perform binding.
	if (bind(sock->sockfd(), (struct sockaddr *)&inaddr, sizeof(inaddr)) != 0) {
		perror("ClosedSocketState::passiveOpen()");
		return false;
	}

	// Perform listen if it's a TCP socket.
	if ((dynamic_cast<TCPSocket *>(sock))) {
		if (listen(sock->sockfd(), qlen) < 0) {
			perror("ClosedSocketState::passiveOpen()");
			return false;
		}
	}

	sock->changeState(BoundSocketState::instance());
	return true;
}

ssize_t ClosedSocketState::sendto(AbstractSocket *sock, const char *buf,
		size_t size, const HostAddress &addr, unsigned short port)
{
	if (!(dynamic_cast<UDPSocket *>(sock))) {
		fprintf(stderr, "ClosedSocketState::sendto(): Error: sendto in closed mode is only suitable for UDP sockets.\n");
		return 0;
	}

	ssize_t result;
	sockaddr_in inaddr;

	// Clear and set address/port.
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = addr.toInetAddr();
	inaddr.sin_port = htons(port);

	if ((result = ::sendto(sock->sockfd(), buf, size, 0,
			(struct sockaddr *)&inaddr,	sizeof(inaddr))) < 0) {
		perror("ClosedSocketState::sendto()");
	}

	return result;
}

/**
 * \internal
 * Private method to initialize a given socket.
 */
bool ClosedSocketState::_initialize(AbstractSocket *sock)
{
	int type;
	int sockfd;

	// Check type.
	if (dynamic_cast<UDPSocket *>(sock))
		type = SOCK_DGRAM;
	else if (dynamic_cast<TCPSocket *>(sock))
		type = SOCK_STREAM;
	else {
		fprintf(stderr, "ClosedSocketState::_initialize(): Error: Unsupported type.\n");
		return false;
	}

	// Initialize.
	if ((sockfd = socket(AF_INET, type, 0)) < 0) {
		perror("ClosedSocketState::_initialize()");
		return false;
	}
	sock->setSockfd(sockfd);

	return true;
}

}
