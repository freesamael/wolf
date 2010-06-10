/**
 * \file SimpleActiveSocketState.cpp
 * \date Apr 6, 2010
 * \author samael
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

namespace cml
{

SINGLETON_REGISTRATION(SimpleActiveSocketState);
SINGLETON_REGISTRATION_END();

bool SimpleActiveSocketState::activeOpen(AbstractSocket *sock,
		const HostAddress &addr, uint16_t port)
{
	// Clear and set address/port.
	sockaddr_in inaddr;
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = addr.toInetAddr();
	inaddr.sin_port = htons(port);

	// Perform connection.
	PINFO_3("Connecting to a remote host.");
	if (connect(sock->sockfd(), (struct sockaddr *)&inaddr, sizeof(inaddr)) != 0) {
		perror("Error: SimpleActiveSocketState::activeOpen()");
		return false;
	}

	sock->changeState(ConnectedSocketState::instance());
	return true;
}

bool SimpleActiveSocketState::passiveOpen(AbstractSocket *sock,
		uint16_t port, int qlen)
{
	// Clear and set inet address/port.
	sockaddr_in inaddr;
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = INADDR_ANY;
	inaddr.sin_port = htons(port);

	// Perform binding.
	PINFO_3("Binding a port.");
	if (bind(sock->sockfd(), (struct sockaddr *)&inaddr, sizeof(inaddr)) != 0) {
		perror("Error: SimpleActiveSocketState::passiveOpen()");
		return false;
	}

	// Perform listen if it's a TCP socket.
	if ((dynamic_cast<TCPSocket *>(sock))) {
		PINFO_3("Listening for connections.");
		if (listen(sock->sockfd(), qlen) < 0) {
			perror("Error: SimpleActiveSocketState::passiveOpen()");
			return false;
		}
	}

	sock->changeState(BoundSocketState::instance());
	return true;
}

bool SimpleActiveSocketState::close(AbstractSocket *sock)
{
	PINFO_3("Closing the socket.");
	if (::close(sock->sockfd()) != 0) {
		perror("Error: ConnectedSocketState::close(): close");
		return false;
	}

	sock->changeState(ClosedSocketState::instance());
	return true;
}

ssize_t SimpleActiveSocketState::recvfrom(AbstractSocket *sock, char *buf,
		size_t size, HostAddress *addr, uint16_t *port)
{
	if (!(dynamic_cast<UDPSocket *>(sock))) {
		PERR("recvfrom is only suitable for UDP sockets.");
		return -1;
	}

	ssize_t result;
	struct sockaddr_in inaddr;
	socklen_t alen = sizeof(inaddr);

	PINFO_3("Receiving an incoming message.");
	if ((result = ::recvfrom(sock->sockfd(), buf, size, 0,
			(struct sockaddr *)&inaddr, &alen)) < 0) {
		perror("Error: SimpleActiveSocketState::recvfrom()");
	}

	addr->setAddr(inaddr.sin_addr.s_addr);
	*port = ntohs(inaddr.sin_port);

	return result;
}

ssize_t SimpleActiveSocketState::sendto(AbstractSocket *sock, const char *buf,
		size_t size, const HostAddress &addr, uint16_t port)
{
	if (!(dynamic_cast<UDPSocket *>(sock))) {
		PERR("sendto is only suitable for UDP sockets.");
		return -1;
	}

	ssize_t result;
	sockaddr_in inaddr;

	// Clear and set address/port.
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = addr.toInetAddr();
	inaddr.sin_port = htons(port);

	PINFO_3("Sending an outgoing message.");
	if ((result = ::sendto(sock->sockfd(), buf, size, 0,
			(struct sockaddr *)&inaddr,	sizeof(inaddr))) < 0) {
		perror("Error: SimpleActiveSocketState::sendto()");
	}

	return result;
}



}
