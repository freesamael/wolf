/**
 * \file CBoundSocketState.cpp
 * \date Apr 5, 2010
 * \author samael
 */

#include "CBoundSocketState.h"

#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "CClosedSocketState.h"
#include "CConnectedSocketState.h"
#include "CSingletonAutoDestructor.h"
#include "ASocket.h"

using namespace std;

namespace wolf
{

SINGLETON_REGISTRATION(CBoundSocketState);
SINGLETON_REGISTRATION_END();

void CBoundSocketState::close(ASocket *sock)
{
	if (::close(sock->sockfd()) != 0)
		throw XSocket(errno);

	sock->changeState(CClosedSocketState::instance());
}

int CBoundSocketState::accept(ASocket *sock)
{
	int insock;
	struct sockaddr_in inaddr;
	socklen_t addlen = sizeof(inaddr);

	if ((insock = ::accept(sock->sockfd(), (struct sockaddr *)&inaddr,
			&addlen)) < 0) {
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return -1; // Nonblocking and no connection.
		else
			throw XSocket(errno);
	}

	return insock;
}

ssize_t CBoundSocketState::recvfrom(ASocket *sock, char *buf, size_t size,
		CHostAddress *addr, in_port_t *port)
{
	ssize_t result;
	struct sockaddr_in inaddr;
	socklen_t alen = sizeof(inaddr);

	if ((result = ::recvfrom(sock->sockfd(), buf, size, 0,
			(struct sockaddr *)&inaddr, &alen)) < 0) {
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return 0; // Nonblocking and no data.
		else
			throw XSocket(errno);
	}

	addr->setAddr(inaddr.sin_addr.s_addr);
	*port = ntohs(inaddr.sin_port);
	return result;
}

ssize_t CBoundSocketState::sendto(ASocket *sock, const char *buf,
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
			(struct sockaddr *)&inaddr, sizeof(inaddr))) < 0) {
		throw XSocket(errno);
	}

	return result;
}

}
