/**
 * \file CClosedSocketState.cpp
 * \date Apr 5, 2010
 * \author samael
 */

#include <cstring>
#include <errno.h>
#include <sys/socket.h>
#include "CClosedSocketState.h"
#include "CSimpleActiveSocketState.h"
#include "CSingletonAutoDestructor.h"
#include "ASocket.h"

using namespace std;

namespace cml
{

SINGLETON_REGISTRATION(CClosedSocketState);
SINGLETON_REGISTRATION_END();

void CClosedSocketState::activeOpen(ASocket *sock, SocketType type,
		const CHostAddress &addr, in_port_t port) throw(XSocket)
{
	open(sock, type);
	sock->activeOpen(addr, port);
}

void CClosedSocketState::passiveOpen(ASocket *sock, SocketType type,
		in_port_t port, int qlen, bool reuse) throw(XSocket)
{
	open(sock, type);
	sock->passiveOpen(port, qlen, reuse);
}

void CClosedSocketState::open(ASocket *sock, SocketType type) throw(XSocket)
{
	int sock_type;
	int sockfd;

	// Check type.
	if (type == UDP)
		sock_type = SOCK_DGRAM;
	else if (type == TCP)
		sock_type = SOCK_STREAM;
	else
		throw XSocket(__PRETTY_FUNCTION__, __LINE__,
				XSocket::INVALID_SOCKET_TYPE);

	// Initialize.
	if ((sockfd = socket(AF_INET, sock_type, 0)) < 0)
		throw XSocket(__PRETTY_FUNCTION__, __LINE__, errno);
	sock->setSockfd(sockfd);
	sock->changeState(CSimpleActiveSocketState::instance());
}

}
