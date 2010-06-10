/**
 * \file ClosedSocketState.cpp
 * \date Apr 5, 2010
 * \author samael
 */

#include <cstdio>
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "ClosedSocketState.h"
#include "SimpleActiveSocketState.h"
#include "TCPSocket.h"
#include "UDPSocket.h"
#include "SingletonAutoDestructor.h"

using namespace std;

namespace cml
{

SINGLETON_REGISTRATION(ClosedSocketState);
SINGLETON_REGISTRATION_END();

bool ClosedSocketState::activeOpen(AbstractSocket *sock,
		const HostAddress &addr, uint16_t port)
{
	PINFO_3("Actively opening a socket.");
	if (open(sock))
		return sock->activeOpen(addr, port);
	return false;
}

bool ClosedSocketState::passiveOpen(AbstractSocket *sock,
		uint16_t port, int qlen)
{
	PINFO_3("Passively opening a socket");
	if (open(sock))
		return sock->passiveOpen(port, qlen);
	return false;
}

bool ClosedSocketState::open(AbstractSocket *sock)
{
	int type;
	int sockfd;

	// Check type.
	if (dynamic_cast<UDPSocket *>(sock))
		type = SOCK_DGRAM;
	else if (dynamic_cast<TCPSocket *>(sock))
		type = SOCK_STREAM;
	else {
		PERR("Unsupported type.");
		return false;
	}

	// Initialize.
	PINFO_3("Opening a socket.");
	if ((sockfd = socket(AF_INET, type, 0)) < 0) {
		perror("Error: ClosedSocketState::open()");
		return false;
	}
	sock->setSockfd(sockfd);
	sock->changeState(SimpleActiveSocketState::instance());

	return true;
}

}
