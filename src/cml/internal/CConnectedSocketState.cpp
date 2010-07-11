/**
 * \file CConnectedSocketState.cpp
 * \date Apr 5, 2010
 * \author samael
 */

#include <errno.h>
#include <sys/socket.h>
#include "CConnectedSocketState.h"
#include "CClosedSocketState.h"
#include "CTcpSocket.h"
#include "CSingletonAutoDestructor.h"

namespace cml
{

SINGLETON_REGISTRATION(CConnectedSocketState);
SINGLETON_REGISTRATION_END();

void CConnectedSocketState::close(ASocket *sock) throw(XSocket)
{
	if (shutdown(sock->sockfd(), SHUT_RDWR) != 0)
		if (errno != ENOTCONN)	// If it's not connected (ENOTCONN), just skip.
			throw XSocket(errno);

	if (::close(sock->sockfd()) != 0)
		throw XSocket(errno);

	sock->changeState(CClosedSocketState::instance());
}

ssize_t CConnectedSocketState::read(ASocket *sock, char *buf, size_t size)
		throw(XSocket)
{
	ssize_t result;
	if ((result = ::read(sock->sockfd(), buf, size)) < 0)
		throw XSocket(errno);
	return result;
}

ssize_t CConnectedSocketState::write(ASocket *sock, const char *buf,
		size_t size) throw(XSocket)
{
	ssize_t result;
	if ((result = ::write(sock->sockfd(), buf, size)) < 0)
		throw XSocket(errno);
	return result;
}

}
