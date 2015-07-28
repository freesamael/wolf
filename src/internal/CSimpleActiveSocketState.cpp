/**
 * \file CSimpleActiveSocketState.cpp
 * \date Apr 6, 2010
 * \author samael
 */

#include "CSimpleActiveSocketState.h"

#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "CClosedSocketState.h"
#include "CConnectedSocketState.h"
#include "CBoundSocketState.h"
#include "CSingletonAutoDestructor.h"
#include "ASocket.h"

// using namespace std;

namespace wolf
{

SINGLETON_REGISTRATION(CSimpleActiveSocketState);
SINGLETON_REGISTRATION_END();

void CSimpleActiveSocketState::activeOpen(ASocket *sock, SocketType UNUSED(type),
		const CHostAddress &addr, in_port_t port)
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

void CSimpleActiveSocketState::passiveOpen(ASocket *sock, SocketType type,
		in_port_t port, int qlen, bool reuse)
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
	if (type == TCP)
		if (listen(sock->sockfd(), qlen) < 0)
			throw XSocket(errno);

	sock->changeState(CBoundSocketState::instance());
}

void CSimpleActiveSocketState::close(ASocket *sock)
{
	if (::close(sock->sockfd()) != 0)
		throw XSocket(errno);
	sock->changeState(CClosedSocketState::instance());
}

ssize_t CSimpleActiveSocketState::recvfrom(ASocket *sock, char *buf,
		size_t size, CHostAddress *addr, in_port_t *port)
{
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
		size_t size, const CHostAddress &addr, in_port_t port)
{
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
