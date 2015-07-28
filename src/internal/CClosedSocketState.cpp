/**
 * \file CClosedSocketState.cpp
 * \date Apr 5, 2010
 * \author samael
 */

#include "CClosedSocketState.h"

#include <cstring>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "CSimpleActiveSocketState.h"
#include "CSingletonAutoDestructor.h"
#include "ASocket.h"

using namespace std;

namespace wolf
{

SINGLETON_REGISTRATION(CClosedSocketState);
SINGLETON_REGISTRATION_END();

void CClosedSocketState::activeOpen(ASocket *sock, SocketType type,
		const CHostAddress &addr, in_port_t port)
{
	open(sock, type);
	sock->activeOpen(addr, port);
}

void CClosedSocketState::passiveOpen(ASocket *sock, SocketType type,
		in_port_t port, int qlen, bool reuse)
{
	open(sock, type);
	sock->passiveOpen(port, qlen, reuse);
}

void CClosedSocketState::open(ASocket *sock, SocketType type)
{
	int sock_type;
	int sockfd;

	// Check type.
	if (type == UDP)
		sock_type = SOCK_DGRAM;
	else if (type == TCP)
		sock_type = SOCK_STREAM;
	else
		throw XSocket(XSocket::INVALID_SOCKET_TYPE);

	// Initialize.
	if ((sockfd = socket(AF_INET, sock_type, 0)) < 0)
		throw XSocket(errno);
	sock->setSockfd(sockfd);
	sock->changeState(CSimpleActiveSocketState::instance());
}

}
