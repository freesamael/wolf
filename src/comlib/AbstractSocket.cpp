/**
 * \file AbstractSocket.cpp
 * \date Mar 8, 2010
 * \author samael
 */

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
#include "ClosedSocketState.h"
#include "SimpleActiveSocketState.h"
#include "HelperMacros.h"

using namespace std;

namespace cml
{

AbstractSocket::AbstractSocket():
		_state(ClosedSocketState::instance())
{
	pthread_mutex_init(&_mutex, NULL);
}

AbstractSocket::AbstractSocket(int sock):
		_sockfd(sock), _state(SimpleActiveSocketState::instance())
{
	pthread_mutex_init(&_mutex, NULL);
}

/**
 * It automatically closes the socket on destruction.
 */
AbstractSocket::~AbstractSocket()
{
	_state->close(this);
	if (pthread_mutex_destroy(&_mutex) != 0)
		perror("Error: AbstractSocket::~AbstractSocket(): Destroying mutex");
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
 * Read a message.
 *
 * \return
 * Size read. On error, return -1.
 */
ssize_t AbstractSocket::read(char *buf, size_t size)
{
	return _state->read(this, buf, size);
}

/**
 * Write a message.
 *
 * \return
 * Size written. On error, return -1.
 */
ssize_t AbstractSocket::write(const char *buf, size_t size)
{
	pthread_mutex_lock(&_mutex);
	ssize_t result = _state->write(this, buf, size);
	pthread_mutex_unlock(&_mutex);
	return result;
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

HostAddress AbstractSocket::currentAddress() const
{
	sockaddr_in inaddr;
	socklen_t len = sizeof(inaddr);

	if (getsockname(_sockfd, (sockaddr *)&inaddr, &len)) {
		perror("Error: AbstractSocket::getSocketName()");
		return HostAddress();
	}
	return HostAddress(inaddr.sin_addr.s_addr);
}

/**
 * Get host address by host name (e.g. "www.google.com").
 */
HostAddress AbstractSocket::getHostByName(const string &host)
{
	hostent *phe;

	if ((phe = gethostbyname(host.c_str()))) {
		in_addr addr;
		memcpy(&addr, phe->h_addr_list[0], phe->h_length);
		return addr.s_addr;
	}
	return INADDR_NONE;
}

/**
 * Get port number by service name (e.g. "http").
 */
uint16_t AbstractSocket::getServiceByName(const string &service)
{
	servent *pse;

	if ((pse = getservbyname(service.c_str(), NULL))) {
		return pse->s_port;
	}
	return 0;
}

}
