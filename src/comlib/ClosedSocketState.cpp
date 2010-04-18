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
#include "HelperMacros.h"

using namespace std;

namespace cml
{

SINGLETON_REGISTRATION(ClosedSocketState);

ClosedSocketState *ClosedSocketState::_instance = NULL;

ClosedSocketState* ClosedSocketState::instance()
{
	if (!_instance)
		_instance = new ClosedSocketState();
	return _instance;
}

void ClosedSocketState::release()
{
	delete _instance;
	_instance = NULL;
}

bool ClosedSocketState::activeOpen(AbstractSocket *sock,
		const HostAddress &addr, uint16_t port)
{
	PINFO("Actively opening a socket.");
	if (open(sock))
		return sock->activeOpen(addr, port);
	return false;
}

bool ClosedSocketState::passiveOpen(AbstractSocket *sock,
		uint16_t port, int qlen)
{
	PINFO("Passively opening a socket");
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
		PERR << "Unsupported type.\n";
		return false;
	}

	// Initialize.
	PINFO("Opening a socket.");
	if ((sockfd = socket(AF_INET, type, 0)) < 0) {
		perror("Error: ClosedSocketState::open()");
		return false;
	}
	sock->setSockfd(sockfd);
	sock->changeState(SimpleActiveSocketState::instance());

	return true;
}

}
