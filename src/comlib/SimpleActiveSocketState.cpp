/*
 * SimpleActiveSocketState.cpp
 *
 *  Created on: Apr 6, 2010
 *      Author: samael
 */

#include <cstdio>
#include <cstring>
#include <errno.h>
#include <arpa/inet.h>
#include "SimpleActiveSocketState.h"
#include "ClosedSocketState.h"
#include "ConnectedSocketState.h"
#include "BoundSocketState.h"
#include "TCPSocket.h"
#include "UDPSocket.h"
#include "SingletonAutoDestructor.h"
#include "HelperMacros.h"

namespace cml
{

SINGLETON_REGISTRATION(SimpleActiveSocketState);

SimpleActiveSocketState *SimpleActiveSocketState::_instance = NULL;

SimpleActiveSocketState* SimpleActiveSocketState::instance()
{
	if (!_instance)
		_instance = new SimpleActiveSocketState();
	return _instance;
}

void SimpleActiveSocketState::release()
{
	delete _instance;
	_instance = NULL;
}

bool SimpleActiveSocketState::activeOpen(AbstractSocket *sock,
		const HostAddress &addr, unsigned short port)
{
	// Clear and set address/port.
	sockaddr_in inaddr;
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = addr.toInetAddr();
	inaddr.sin_port = htons(port);

	// Perform connection.
	if (connect(sock->sockfd(), (struct sockaddr *)&inaddr, sizeof(inaddr)) != 0) {
		perror("SimpleActiveSocketState::activeOpen()");
		return false;
	}

	sock->changeState(ConnectedSocketState::instance());
	return true;
}

bool SimpleActiveSocketState::passiveOpen(AbstractSocket *sock,
		unsigned short port, int qlen)
{
	// Clear and set inet address/port.
	sockaddr_in inaddr;
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = INADDR_ANY;
	inaddr.sin_port = htons(port);

	// Perform binding.
	if (bind(sock->sockfd(), (struct sockaddr *)&inaddr, sizeof(inaddr)) != 0) {
		perror("SimpleActiveSocketState::passiveOpen()");
		return false;
	}

	// Perform listen if it's a TCP socket.
	if ((dynamic_cast<TCPSocket *>(sock))) {
		if (listen(sock->sockfd(), qlen) < 0) {
			perror("SimpleActiveSocketState::passiveOpen()");
			return false;
		}
	}

	sock->changeState(BoundSocketState::instance());
	return true;
}

bool SimpleActiveSocketState::close(AbstractSocket *sock)
{
	if (::close(sock->sockfd()) != 0) {
		perror("ConnectedSocketState::close(): close");
		return false;
	}

	sock->changeState(ClosedSocketState::instance());
	return true;
}

ssize_t SimpleActiveSocketState::recvfrom(AbstractSocket *sock, char *buf,
		size_t size, HostAddress *addr, unsigned short *port)
{
	if (!(dynamic_cast<UDPSocket *>(sock))) {
		fprintf(stderr, "SimpleActiveSocketState::recvfrom(): Error: recvfrom is only suitable for UDP sockets.\n");
		return -1;
	}

	ssize_t result;
	struct sockaddr_in inaddr;
	socklen_t alen = sizeof(inaddr);

	if ((result = ::recvfrom(sock->sockfd(), buf, size, 0,
			(struct sockaddr *)&inaddr, &alen)) < 0) {
		perror("SimpleActiveSocketState::recvfrom()");
	}

	addr->setAddr(inaddr.sin_addr.s_addr);
	*port = ntohs(inaddr.sin_port);

	return result;
}

ssize_t SimpleActiveSocketState::sendto(AbstractSocket *sock, const char *buf,
		size_t size, const HostAddress &addr, unsigned short port)
{
	if (!(dynamic_cast<UDPSocket *>(sock))) {
		fprintf(stderr, "SimpleActiveSocketState::sendto(): Error: sendto is only suitable for UDP sockets.\n");
		return -1;
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
		perror("SimpleActiveSocketState::sendto()");
	}

	return result;
}



}
