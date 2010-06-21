/**
 * \file AbstractSocket.cpp
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
#include "AbstractSocket.h"
#include "ITLVObject.h"
#include "TLVObjectFactory.h"
#include "TLVBlock.h"
#include "internal/ClosedSocketState.h"
#include "internal/SimpleActiveSocketState.h"
#include "internal/BoundSocketState.h"
#include "internal/ConnectedSocketState.h"
#include "HelperMacros.h"

using namespace std;

namespace cml
{

const string AbstractSocket::ClosedState = ClosedSocketState::instance()->name();
const string AbstractSocket::ActiveState = SimpleActiveSocketState::instance()->name();
const string AbstractSocket::BoundState = BoundSocketState::instance()->name();
const string AbstractSocket::ConnectedState = ConnectedSocketState::instance()->name();

AbstractSocket::AbstractSocket():
		_sockfd(0), _wmx(), _rmx(), _state(ClosedSocketState::instance())
{
}

AbstractSocket::AbstractSocket(const AbstractSocket &sock):
		_sockfd(sock._sockfd), _wmx(), _rmx(), _state(sock._state)
{
}

AbstractSocket::AbstractSocket(int sockfd):
		_sockfd(sockfd), _wmx(), _rmx(),
		_state(SimpleActiveSocketState::instance())
{
}

/**
 * It automatically closes the socket on destruction.
 */
AbstractSocket::~AbstractSocket()
{
	_state->close(this);
}

/**
 * Operator =
 */
AbstractSocket& AbstractSocket::operator=(const AbstractSocket &sock)
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
bool AbstractSocket::open()
{
	return _state->open(this);
}

/**
 * Actively open the socket (connect to a host).
 *
 * \return
 * True on success, false otherwise.
 */
bool AbstractSocket::activeOpen(const HostAddress &addr, uint16_t port)
{
	return _state->activeOpen(this, addr, port);
}

/**
 * Passively open the socket (bind or listen on specific port).
 *
 * \return
 * True on success, false otherwise.
 */
bool AbstractSocket::passiveOpen(uint16_t port, int qlen)
{
	return _state->passiveOpen(this, port, qlen);
}

bool AbstractSocket::close()
{
	return _state->close(this);
}

/**
 * Read a message. It's not thread-safe unless you use lockread() and
 * unlockread() in your program.
 *
 * \return
 * Size read. On error, return -1.
 */
ssize_t AbstractSocket::read(char *buf, size_t size)
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
ssize_t AbstractSocket::write(const char *buf, size_t size)
{
	return _state->write(this, buf, size);;
}

/**
 * Set if the socket should be nonblocking.
 *
 * \return
 * True on success, false on failure.
 */
bool AbstractSocket::setNonblock(bool nonblk)
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
bool AbstractSocket::isNonblock() const
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
bool AbstractSocket::setTTL(int ttl)
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
int AbstractSocket::TTL() const
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
HostAddress AbstractSocket::currentAddress() const
{
	sockaddr_in inaddr;
	socklen_t len = sizeof(inaddr);

	if (getsockname(_sockfd, (sockaddr *)&inaddr, &len)) {
		perror("Error: AbstractSocket::currentAddress()");
		return HostAddress();
	}
	return HostAddress(inaddr.sin_addr.s_addr);
}

/**
 * Get the address of connected peer.
 */
HostAddress AbstractSocket::peerAddress() const
{
	sockaddr_in inaddr;
	socklen_t len = sizeof(inaddr);

	if (getpeername(_sockfd, (sockaddr *)&inaddr, &len)) {
		perror("Error: AbstractSocket::peerAddress()");
		return HostAddress();
	}
	return HostAddress(inaddr.sin_addr.s_addr);
}

/**
 * Register a release() function of a singleton object to all singleton socket
 * objects. It's used by SINGLETON_DEPENDS_SOCKET() macro, and is not supposed
 * to be called manually by users.
 */
void AbstractSocket::registerSocketDependant(void (*rls)())
{
	ClosedSocketState::instance()->registerDependant(rls);
	SimpleActiveSocketState::instance()->registerDependant(rls);
	BoundSocketState::instance()->registerDependant(rls);
	ConnectedSocketState::instance()->registerDependant(rls);
}

}
