/**
 * \file CConnectedSocketState.cpp
 * \date Apr 5, 2010
 * \author samael
 */

#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "CConnectedSocketState.h"
#include "CClosedSocketState.h"
#include "CSingletonAutoDestructor.h"
#include "ASocket.h"

namespace wolf
{

SINGLETON_REGISTRATION(CConnectedSocketState);
SINGLETON_REGISTRATION_END();

void CConnectedSocketState::close(ASocket *sock)
{
	if (shutdown(sock->sockfd(), SHUT_RDWR) != 0)
		if (errno != ENOTCONN)	// If it's not connected (ENOTCONN), just skip.
			throw XSocket(errno);

	if (::close(sock->sockfd()) != 0)
		throw XSocket(errno);

	sock->changeState(CClosedSocketState::instance());
}

ssize_t CConnectedSocketState::read(ASocket *sock, char *buf, size_t size)

{
	ssize_t result;
	if ((result = ::read(sock->sockfd(), buf, size)) < 0) {
		// No padding data.
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return 0;

		// Connection ends (end-of-file).
		if (errno == ENOTCONN) {
			close(sock);
			return 0;
		}

		throw XSocket(errno);
	}
	return result;
}

ssize_t CConnectedSocketState::write(ASocket *sock, const char *buf,
		size_t size)
{
	ssize_t result;
	if ((result = ::write(sock->sockfd(), buf, size)) < 0) {
		// Non-blocking socket while write might block.
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return 0;

		// Connection ends.
		if (errno == ENOTCONN) {
			close(sock);
			return 0;
		}
		throw XSocket(errno);
	}
	return result;
}

}
