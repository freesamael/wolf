/**
 * \file CBoundSocketState.cpp
 * \date Apr 5, 2010
 * \author samael
 */

#include <cstdio>
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "CBoundSocketState.h"
#include "CClosedSocketState.h"
#include "CConnectedSocketState.h"
#include "CUdpSocket.h"
#include "CTcpSocket.h"
#include "CSingletonAutoDestructor.h"

using namespace std;

namespace cml
{

SINGLETON_REGISTRATION(CBoundSocketState);
SINGLETON_REGISTRATION_END();

bool CBoundSocketState::close(ASocket *sock)
{
	PINF_3("Closing Socket.");
	if (::close(sock->sockfd()) != 0) {
		perror("Error: BoundSocketState::close(): close");
		return false;
	}

	sock->changeState(CClosedSocketState::instance());
	return true;
}

CTcpSocket* CBoundSocketState::accept(ASocket *sock)
{
	struct sockaddr_in inaddr;
	socklen_t addlen = sizeof(inaddr);
	int insock;

	PINF_3("Waiting for incoming connections.");
	if ((insock = ::accept(sock->sockfd(), (struct sockaddr *)&inaddr,
			&addlen)) < 0) {
		if (!(sock->isNonblock() && (errno == EAGAIN || errno == EWOULDBLOCK)))
			perror("Error: BoundSocketState::accept()");
		return NULL;
	}

	PINF_3("Got an incoming connection.");
	CTcpSocket *tcpsock = new CTcpSocket(insock);
	tcpsock->changeState(CConnectedSocketState::instance());

	return tcpsock;
}

ssize_t CBoundSocketState::recvfrom(ASocket *sock, char *buf, size_t size,
		CHostAddress *addr, uint16_t *port)
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
		perror("Error: BoundSocketState::recvfrom()");
	}
	PINF_3(result << " bytes received.");

	addr->setAddr(inaddr.sin_addr.s_addr);
	*port = ntohs(inaddr.sin_port);

	return result;
}

ssize_t CBoundSocketState::sendto(ASocket *sock, const char *buf,
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
			(struct sockaddr *)&inaddr, sizeof(inaddr))) < 0) {
		perror("Error: BoundSocketState::sendto()");
	}
	PINF_3(result << " bytes sent.");

	return result;
}

}
