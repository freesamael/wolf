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
#include "CTcpSocket.h"
#include "CUdpSocket.h"
#include "CSingletonAutoDestructor.h"

using namespace std;

namespace cml
{

SINGLETON_REGISTRATION(CClosedSocketState);
SINGLETON_REGISTRATION_END();

void CClosedSocketState::activeOpen(ASocket *sock,
		const CHostAddress &addr, uint16_t port) throw(XSocket)
{
	open(sock);
	sock->activeOpen(addr, port);
}

void CClosedSocketState::passiveOpen(ASocket *sock, uint16_t port, int qlen,
		bool reuse)
		throw(XSocket)
{
	open(sock);
	sock->passiveOpen(port, qlen, reuse);
}

void CClosedSocketState::open(ASocket *sock) throw(XSocket)
{
	int type;
	int sockfd;

	// Check type.
	if (dynamic_cast<CUdpSocket *>(sock))
		type = SOCK_DGRAM;
	else if (dynamic_cast<CTcpSocket *>(sock))
		type = SOCK_STREAM;
	else
		throw XSocket(XSocket::INVALID_SOCKET_TYPE);

	// Initialize.
	if ((sockfd = socket(AF_INET, type, 0)) < 0)
		throw XSocket(errno);
	sock->setSockfd(sockfd);
	sock->changeState(CSimpleActiveSocketState::instance());
}

}
