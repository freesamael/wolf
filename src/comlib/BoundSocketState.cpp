/*
 * BoundSocketState.cpp
 *
 *  Created on: Apr 5, 2010
 *      Author: samael
 */

#include <cstdio>
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "BoundSocketState.h"
#include "ClosedSocketState.h"
#include "UDPSocket.h"
#include "TCPSocket.h"

using namespace std;

namespace cml
{

BoundSocketState *BoundSocketState::_instance = NULL;

BoundSocketState* BoundSocketState::instance()
{
	if (!_instance)
		_instance = new BoundSocketState();
	return _instance;
}

bool BoundSocketState::close(AbstractSocket *sock)
{
	if (shutdown(sock->sockfd(), SHUT_RDWR) != 0) {
		perror("BoundSocketState::close(): shutdown");
		return false;
	}

	if (::close(sock->sockfd()) != 0) {
		perror("BoundSocketState::close(): close");
		return false;
	}

	sock->changeState(ClosedSocketState::instance());
	return true;
}

TCPSocket* BoundSocketState::accept(AbstractSocket *sock)
{
	struct sockaddr_in inaddr;
	unsigned addlen = sizeof(inaddr);
	int insock;

	if ((insock = ::accept(sock->sockfd(), (struct sockaddr *)&inaddr,
			&addlen)) < 0) {
		if (!(sock->isNonblock() && (errno == EAGAIN || errno == EWOULDBLOCK)))
			perror("BoundSocketState::accept()");
		return NULL;
	}
	TCPSocket *tcpsock = new TCPSocket(insock);
	return tcpsock;
}

ssize_t BoundSocketState::recvfrom(AbstractSocket *sock, char *buf, size_t size,
		HostAddress *addr, unsigned short *port)
{
	if (!(dynamic_cast<UDPSocket *>(sock))) {
		fprintf(stderr, "BoundSocketState::recvfrom(): Error: recvfrom in passive mode is only suitable for UDP sockets.\n");
		return 0;
	}

	ssize_t result;
	struct sockaddr_in inaddr;
	socklen_t alen = sizeof(inaddr);

	if ((result = ::recvfrom(sock->sockfd(), buf, size, 0,
			(struct sockaddr *)&inaddr, &alen)) < 0) {
		perror("BoundSocketState::recvfrom()");
	}

	addr->setAddr(inaddr.sin_addr.s_addr);
	*port = ntohs(inaddr.sin_port);

	return result;
}

ssize_t BoundSocketState::sendto(AbstractSocket *sock, const char *buf,
		size_t size, const HostAddress &addr, unsigned short port)
{
	if (!(dynamic_cast<UDPSocket *>(sock))) {
		fprintf(stderr, "BoundSocketState::sendto(): Error: sendto in passive mode is only suitable for UDP sockets.\n");
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
			(struct sockaddr *)&inaddr, sizeof(inaddr))) < 0) {
		perror("BoundSocketState::sendto()");
	}

	return result;
}

}
