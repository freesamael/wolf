/**
 * \file CSimpleActiveSocketState.cpp
 * \date Apr 6, 2010
 * \author samael
 */

#include <cstring>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "CSimpleActiveSocketState.h"
#include "CClosedSocketState.h"
#include "CConnectedSocketState.h"
#include "CBoundSocketState.h"
#include "CTcpSocket.h"
#include "CUdpSocket.h"
#include "CSingletonAutoDestructor.h"

using namespace std;

namespace cml
{

SINGLETON_REGISTRATION(CSimpleActiveSocketState);
SINGLETON_REGISTRATION_END();

void CSimpleActiveSocketState::activeOpen(ASocket *sock,
		const CHostAddress &addr, uint16_t port) throw(XSocket)
{
	// Clear and set address/port.
	sockaddr_in inaddr;
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = addr.toInetAddr();
	inaddr.sin_port = htons(port);

	// Perform connection.
	if (connect(sock->sockfd(), (struct sockaddr *)&inaddr, sizeof(inaddr))	!= 0)
		throw XSocket(errno);

	sock->changeState(CConnectedSocketState::instance());
}

void CSimpleActiveSocketState::passiveOpen(ASocket *sock, uint16_t port,
		int qlen, bool reuse) throw(XSocket)
{
	// Clear and set inet address/port.
	sockaddr_in inaddr;
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = INADDR_ANY;
	inaddr.sin_port = htons(port);

	// Reuse port.
	if (reuse) {
		int reuseaddr = 1;
		socklen_t reuseaddr_len = sizeof(reuseaddr);
		if (setsockopt(sock->sockfd(), SOL_SOCKET, SO_REUSEADDR, &reuseaddr,
				reuseaddr_len) != 0) {
			throw XSocket(errno);
		}
	}

	// Perform binding.
	if (bind(sock->sockfd(), (struct sockaddr *)&inaddr, sizeof(inaddr)) != 0)
		throw XSocket(errno);

	// Perform listen if it's a TCP socket.
	if ((dynamic_cast<CTcpSocket *>(sock)))
		if (listen(sock->sockfd(), qlen) < 0)
			throw XSocket(errno);

	sock->changeState(CBoundSocketState::instance());
}

void CSimpleActiveSocketState::close(ASocket *sock) throw(XSocket)
{
	if (::close(sock->sockfd()) != 0)
		throw XSocket(errno);
	sock->changeState(CClosedSocketState::instance());
}

ssize_t CSimpleActiveSocketState::recvfrom(ASocket *sock, char *buf,
		size_t size, CHostAddress *addr, uint16_t *port) throw(XSocket)
{
	if (!(dynamic_cast<CUdpSocket *>(sock)))
		throw XSocket(XSocket::INVALID_SOCKET_TYPE);

	ssize_t result;
	struct sockaddr_in inaddr;
	socklen_t alen = sizeof(inaddr);

	if ((result = ::recvfrom(sock->sockfd(), buf, size, 0,
			(struct sockaddr *)&inaddr, &alen)) < 0) {
		throw XSocket(errno);
	}

	addr->setAddr(inaddr.sin_addr.s_addr);
	*port = ntohs(inaddr.sin_port);
	return result;
}

ssize_t CSimpleActiveSocketState::sendto(ASocket *sock, const char *buf,
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
			(struct sockaddr *)&inaddr,	sizeof(inaddr))) < 0) {
		throw XSocket(errno);
	}

	return result;
}

}
