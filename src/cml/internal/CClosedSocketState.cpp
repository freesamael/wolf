/**
 * \file CClosedSocketState.cpp
 * \date Apr 5, 2010
 * \author samael
 */

#include <cstdio>
#include <cstring>
#include <errno.h>
#include <sys/types.h>
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

bool CClosedSocketState::activeOpen(ASocket *sock,
		const CHostAddress &addr, uint16_t port)
{
	PINF_3("Actively opening a socket.");
	if (open(sock))
		return sock->activeOpen(addr, port);
	return false;
}

bool CClosedSocketState::passiveOpen(ASocket *sock,
		uint16_t port, int qlen)
{
	PINF_3("Passively opening a socket");
	if (open(sock))
		return sock->passiveOpen(port, qlen);
	return false;
}

bool CClosedSocketState::open(ASocket *sock)
{
	int type;
	int sockfd;

	// Check type.
	if (dynamic_cast<CUdpSocket *>(sock))
		type = SOCK_DGRAM;
	else if (dynamic_cast<CTcpSocket *>(sock))
		type = SOCK_STREAM;
	else {
		PERR("Unsupported type.");
		return false;
	}

	// Initialize.
	PINF_3("Opening a socket.");
	if ((sockfd = socket(AF_INET, type, 0)) < 0) {
		perror("Error: ClosedSocketState::open()");
		return false;
	}
	sock->setSockfd(sockfd);
	sock->changeState(CSimpleActiveSocketState::instance());

	return true;
}

}
