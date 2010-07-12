/**
 * \file CBoundSocketState.cpp
 * \date Apr 5, 2010
 * \author samael
 */

#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
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

void CBoundSocketState::close(ASocket *sock) throw(XSocket)
{
	if (::close(sock->sockfd()) != 0)
		throw XSocket(errno);

	sock->changeState(CClosedSocketState::instance());
}

CTcpSocket* CBoundSocketState::accept(ASocket *sock) throw(XSocket)
{
	int insock;
	struct sockaddr_in inaddr;
	socklen_t addlen = sizeof(inaddr);

	if ((insock = ::accept(sock->sockfd(), (struct sockaddr *)&inaddr,
			&addlen)) < 0) {
		if (sock->isNonblock() && (errno == EAGAIN || errno == EWOULDBLOCK))
			return NULL; // Nonblocking and no connection.
		else
			throw XSocket(errno);
	}

	CTcpSocket *tcpsock = new CTcpSocket(insock);
	tcpsock->changeState(CConnectedSocketState::instance());
	return tcpsock;
}

ssize_t CBoundSocketState::recvfrom(ASocket *sock, char *buf, size_t size,
		CHostAddress *addr, uint16_t *port) throw(XSocket)
{
	if (!(dynamic_cast<CUdpSocket *>(sock)))
		throw XSocket(XSocket::INVALID_SOCKET_TYPE);

	ssize_t result;
	struct sockaddr_in inaddr;
	socklen_t alen = sizeof(inaddr);

	if ((result = ::recvfrom(sock->sockfd(), buf, size, 0,
			(struct sockaddr *)&inaddr, &alen)) < 0) {
		if (sock->isNonblock() && (errno == EAGAIN || errno == EWOULDBLOCK))
			return 0; // Nonblocking and no data.
		else
			throw XSocket(errno);
	}

	addr->setAddr(inaddr.sin_addr.s_addr);
	*port = ntohs(inaddr.sin_port);
	return result;
}

ssize_t CBoundSocketState::sendto(ASocket *sock, const char *buf,
		size_t size, const CHostAddress &addr, uint16_t port) throw(XSocket)
{
	if (!(dynamic_cast<CUdpSocket *>(sock)))
		throw XSocket(XSocket::INVALID_SOCKET_TYPE);

	ssize_t result;
	sockaddr_in inaddr;

	// Clear and set address/port.
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = addr.toInetAddr();
	inaddr.sin_port = htons(port);

	if ((result = ::sendto(sock->sockfd(), buf, size, 0,
			(struct sockaddr *)&inaddr, sizeof(inaddr))) < 0) {
		throw XSocket(errno);
	}

	return result;
}

}
