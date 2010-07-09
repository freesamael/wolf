/**
 * \file ASocket.cpp
 * \date Mar 8, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "ASocket.h"
#include "ITlvObject.h"
#include "CTlvObjectFactory.h"
#include "CTlvBlock.h"
#include "internal/CClosedSocketState.h"
#include "internal/CSimpleActiveSocketState.h"
#include "internal/CBoundSocketState.h"
#include "internal/CConnectedSocketState.h"
#include "HelperMacros.h"

using namespace std;

namespace cml
{

const string ASocket::ClosedState = CClosedSocketState::instance()->name();
const string ASocket::ActiveState = CSimpleActiveSocketState::instance()->name();
const string ASocket::BoundState = CBoundSocketState::instance()->name();
const string ASocket::ConnectedState = CConnectedSocketState::instance()->name();

ASocket::ASocket():
		_sockfd(0), _wmx(), _rmx(), _state(CClosedSocketState::instance())
{
}

ASocket::ASocket(const ASocket &sock):
		_sockfd(sock._sockfd), _wmx(), _rmx(), _state(sock._state)
{
}

ASocket::ASocket(int sockfd):
		_sockfd(sockfd), _wmx(), _rmx(),
		_state(CSimpleActiveSocketState::instance())
{
}

/**
 * It automatically closes the socket on destruction.
 */
ASocket::~ASocket()
{
	_state->close(this);
}

/**
 * Operator =
 */
ASocket& ASocket::operator=(const ASocket &sock)
{
	_sockfd = sock._sockfd;
	_state = sock._state;
	return *this;
}

/**
 * Open the socket without binding or connection.
 *
 * \return
 * True on success, false otherwise.
 */
bool ASocket::open()
{
	return _state->open(this);
}

/**
 * Actively open the socket (connect to a host).
 *
 * \return
 * True on success, false otherwise.
 */
bool ASocket::activeOpen(const CHostAddress &addr, uint16_t port)
{
	return _state->activeOpen(this, addr, port);
}

/**
 * Passively open the socket (bind or listen on specific port).
 *
 * \return
 * True on success, false otherwise.
 */
bool ASocket::passiveOpen(uint16_t port, int qlen)
{
	return _state->passiveOpen(this, port, qlen);
}

bool ASocket::close()
{
	return _state->close(this);
}

/**
 * Lock write.
 */
bool ASocket::lockwrite()
{
	PINF_3("Lock write.");
	return CConnectedSocketState::instance()->mutex().lock();
}

/**
 * Unlock write.
 */
bool ASocket::unlockwrite()
{
	PINF_3("Unlock write.");
	return CConnectedSocketState::instance()->mutex().unlock();
}

/**
 * Read a message. It's not thread-safe unless you use lockread() and
 * unlockread() in your program.
 *
 * \return
 * Size read. On error, return -1.
 */
ssize_t ASocket::read(char *buf, size_t size)
{
	return _state->read(this, buf, size);
}

/**
 * Write a message. It's not thread-safe unless you use lockwrite() and
 * unlockwrite().
 *
 * \return
 * Size written. On error, return -1.
 */
ssize_t ASocket::write(const char *buf, size_t size)
{
	return _state->write(this, buf, size);;
}

/**
 * Set if the socket should be nonblocking.
 *
 * \return
 * True on success, false on failure.
 */
bool ASocket::setNonblock(bool nonblk)
{
	int arg;

	// Get arg.
	if ((arg = fcntl(_sockfd, F_GETFL, NULL)) < 0) {
		perror("Error: AbstractSocket::setNonblock(): Getting flags");
		return false;
	}

	// Change arg.
	if (nonblk)
		arg |= O_NONBLOCK;
	else
		arg &= (~O_NONBLOCK);

	// Set arg.
	if ((fcntl(_sockfd, F_SETFL, arg)) < 0) {
		perror("Error: AbstractSocket::setNonblock(): Setting flags");
		return false;
	}
	return true;
}

/**
 * Check if the socket is nonblocking.
 */
bool ASocket::isNonblock() const
{
	int arg;

	// Get arg.
	if ((arg = fcntl(_sockfd, F_GETFL, NULL)) < 0) {
		perror("Error: AbstractSocket::isNonblock()");
		return false;
	}

	return (arg & O_NONBLOCK);
}

/**
 * Set the TTL of the socket.
 *
 * \return
 * True on success, false on failure.
 */
bool ASocket::setTTL(int ttl)
{
	if (ttl < 1) {
		PERR("TTL must greater or equal to 1.");
		return false;
	}
	if (setsockopt(_sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0) {
		perror("Error: AbstractSocket::setTTL()");
		return false;
	}
	return true;
}

/**
 * Get the current TTL of the socket.
 */
int ASocket::TTL() const
{
	int ttl;
	socklen_t len = sizeof(ttl);
	if (getsockopt(_sockfd, IPPROTO_IP, IP_TTL, &ttl, &len) < 0) {
		perror("Error: AbstractSocket::TTL()");
		return -1;
	}
	return ttl;
}

/**
 * Get the address currently bound.
 */
CHostAddress ASocket::currentAddress() const
{
	sockaddr_in inaddr;
	socklen_t len = sizeof(inaddr);

	if (getsockname(_sockfd, (sockaddr *)&inaddr, &len)) {
		perror("Error: AbstractSocket::currentAddress()");
		return CHostAddress();
	}
	return CHostAddress(inaddr.sin_addr.s_addr);
}

/**
 * Get the address of connected peer.
 */
CHostAddress ASocket::peerAddress() const
{
	sockaddr_in inaddr;
	socklen_t len = sizeof(inaddr);

	if (getpeername(_sockfd, (sockaddr *)&inaddr, &len)) {
		perror("Error: AbstractSocket::peerAddress()");
		return CHostAddress();
	}
	return CHostAddress(inaddr.sin_addr.s_addr);
}

/**
 * Register a release() function of a singleton object to all singleton socket
 * objects. It's used by SINGLETON_DEPENDS_SOCKET() macro, and is not supposed
 * to be called manually by users.
 */
void ASocket::registerSocketDependant(void (*rls)())
{
	CClosedSocketState::instance()->registerDependant(rls);
	CSimpleActiveSocketState::instance()->registerDependant(rls);
	CBoundSocketState::instance()->registerDependant(rls);
	CConnectedSocketState::instance()->registerDependant(rls);
}

}
