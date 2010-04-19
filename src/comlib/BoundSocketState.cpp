/**
 * \file BoundSocketState.cpp
 * \date Apr 5, 2010
 * \author samael
 */

#include <cstdio>
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "BoundSocketState.h"
#include "ClosedSocketState.h"
#include "ConnectedSocketState.h"
#include "UDPSocket.h"
#include "TCPSocket.h"
#include "SingletonAutoDestructor.h"
#include "HelperMacros.h"

using namespace std;

namespace cml
{

SINGLETON_REGISTRATION(BoundSocketState);

BoundSocketState *BoundSocketState::_instance = NULL;

BoundSocketState* BoundSocketState::instance()
{
	if (!_instance)
		_instance = new BoundSocketState();
	return _instance;
}

void BoundSocketState::release()
{
	delete _instance;
	_instance = NULL;
}

bool BoundSocketState::close(AbstractSocket *sock)
{
	PINFO("Closing Socket.");
	if (::close(sock->sockfd()) != 0) {
		perror("Error: BoundSocketState::close(): close");
		return false;
	}

	sock->changeState(ClosedSocketState::instance());
	return true;
}

TCPSocket* BoundSocketState::accept(AbstractSocket *sock)
{
	struct sockaddr_in inaddr;
	socklen_t addlen = sizeof(inaddr);
	int insock;

	PINFO("Waiting for incoming connections.");
	if ((insock = ::accept(sock->sockfd(), (struct sockaddr *)&inaddr,
			&addlen)) < 0) {
		if (!(sock->isNonblock() && (errno == EAGAIN || errno == EWOULDBLOCK)))
			perror("Error: BoundSocketState::accept()");
		return NULL;
	}

	PINFO("Got an incoming connection.");
	TCPSocket *tcpsock = new TCPSocket(insock);
	tcpsock->changeState(ConnectedSocketState::instance());

	return tcpsock;
}

ssize_t BoundSocketState::recvfrom(AbstractSocket *sock, char *buf, size_t size,
		HostAddress *addr, uint16_t *port)
{
	if (!(dynamic_cast<UDPSocket *>(sock))) {
		PERR("recvfrom is only suitable for UDP sockets.");
		return -1;
	}

	ssize_t result;
	struct sockaddr_in inaddr;
	socklen_t alen = sizeof(inaddr);

	PINFO("Receiving an incoming message.");
	if ((result = ::recvfrom(sock->sockfd(), buf, size, 0,
			(struct sockaddr *)&inaddr, &alen)) < 0) {
		perror("Error: BoundSocketState::recvfrom()");
	}

	addr->setAddr(inaddr.sin_addr.s_addr);
	*port = ntohs(inaddr.sin_port);

	return result;
}

ssize_t BoundSocketState::sendto(AbstractSocket *sock, const char *buf,
		size_t size, const HostAddress &addr, uint16_t port)
{
	if (!(dynamic_cast<UDPSocket *>(sock))) {
		PERR("sendto is only suitable for UDP sockets.");
		return -1;
	}

	ssize_t result;
	sockaddr_in inaddr;

	// Clear and set address/port.
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = addr.toInetAddr();
	inaddr.sin_port = htons(port);

	PINFO("Sending an outgoing message.");
	if ((result = ::sendto(sock->sockfd(), buf, size, 0,
			(struct sockaddr *)&inaddr, sizeof(inaddr))) < 0) {
		perror("Error: BoundSocketState::sendto()");
	}

	return result;
}

}
