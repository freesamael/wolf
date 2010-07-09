/**
 * \file CSimpleActiveSocketState.cpp
 * \date Apr 6, 2010
 * \author samael
 */

#include <cstdio>
#include <cstring>
#include <errno.h>
#include <arpa/inet.h>
#include "CSimpleActiveSocketState.h"
#include "CClosedSocketState.h"
#include "CConnectedSocketState.h"
#include "CBoundSocketState.h"
#include "CTcpSocket.h"
#include "CUdpSocket.h"
#include "CSingletonAutoDestructor.h"

namespace cml
{

SINGLETON_REGISTRATION(CSimpleActiveSocketState);
SINGLETON_REGISTRATION_END();

bool CSimpleActiveSocketState::activeOpen(ASocket *sock,
		const CHostAddress &addr, uint16_t port)
{
	// Clear and set address/port.
	sockaddr_in inaddr;
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = addr.toInetAddr();
	inaddr.sin_port = htons(port);

	// Perform connection.
	PINF_3("Connecting to a remote host.");
	if (connect(sock->sockfd(), (struct sockaddr *)&inaddr, sizeof(inaddr)) != 0) {
		perror("Error: SimpleActiveSocketState::activeOpen()");
		return false;
	}

	sock->changeState(CConnectedSocketState::instance());
	return true;
}

bool CSimpleActiveSocketState::passiveOpen(ASocket *sock,
		uint16_t port, int qlen)
{
	// Clear and set inet address/port.
	sockaddr_in inaddr;
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = INADDR_ANY;
	inaddr.sin_port = htons(port);

	// Reuse port.
	int reuseaddr = 1;
    socklen_t reuseaddr_len = sizeof(reuseaddr);
	setsockopt(sock->sockfd(), SOL_SOCKET, SO_REUSEADDR, &reuseaddr,
			reuseaddr_len);

	// Perform binding.
	PINF_3("Binding a port.");
	if (bind(sock->sockfd(), (struct sockaddr *)&inaddr, sizeof(inaddr)) != 0) {
		perror("Error: SimpleActiveSocketState::passiveOpen()");
		return false;
	}

	// Perform listen if it's a TCP socket.
	if ((dynamic_cast<CTcpSocket *>(sock))) {
		PINF_3("Listening for connections.");
		if (listen(sock->sockfd(), qlen) < 0) {
			perror("Error: SimpleActiveSocketState::passiveOpen()");
			return false;
		}
	}

	sock->changeState(CBoundSocketState::instance());
	return true;
}

bool CSimpleActiveSocketState::close(ASocket *sock)
{
	PINF_3("Closing the socket.");
	if (::close(sock->sockfd()) != 0) {
		perror("Error: ConnectedSocketState::close(): close");
		return false;
	}

	sock->changeState(CClosedSocketState::instance());
	return true;
}

ssize_t CSimpleActiveSocketState::recvfrom(ASocket *sock, char *buf,
		size_t size, CHostAddress *addr, uint16_t *port)
{
	if (!(dynamic_cast<CUdpSocket *>(sock))) {
		PERR("recvfrom is only suitable for UDP sockets.");
		return -1;
	}

	ssize_t result;
	struct sockaddr_in inaddr;
	socklen_t alen = sizeof(inaddr);

	PINF_3("Receiving an incoming message.");
	if ((result = ::recvfrom(sock->sockfd(), buf, size, 0,
			(struct sockaddr *)&inaddr, &alen)) < 0) {
		perror("Error: SimpleActiveSocketState::recvfrom()");
	}
	PINF_3(result << " bytes received.");

	addr->setAddr(inaddr.sin_addr.s_addr);
	*port = ntohs(inaddr.sin_port);

	return result;
}

ssize_t CSimpleActiveSocketState::sendto(ASocket *sock, const char *buf,
		size_t size, const CHostAddress &addr, uint16_t port)
{
	if (!(dynamic_cast<CUdpSocket *>(sock))) {
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

	PINF_3("Sending an outgoing message.");
	if ((result = ::sendto(sock->sockfd(), buf, size, 0,
			(struct sockaddr *)&inaddr,	sizeof(inaddr))) < 0) {
		perror("Error: SimpleActiveSocketState::sendto()");
	}
	PINF_3(result << " bytes sent.");

	return result;
}



}
