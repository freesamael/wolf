/*
 * Socket.cpp
 *
 *  Created on: Mar 8, 2010
 *      Author: samael
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

using namespace std;

namespace cml
{

AbstractSocket::AbstractSocket()
{
	pthread_mutex_init(&_mutex, NULL);
}

AbstractSocket::AbstractSocket(int sock):
		_sockfd(sock)
{
	pthread_mutex_init(&_mutex, NULL);
}

/**
 * \note
 * It closes the socket automatically on destruction. However, in case of TCP
 * socket, users need to call shutdown() before destruction for graceful TCP
 * disconnection.
 */
AbstractSocket::~AbstractSocket()
{
	if (::close(_sockfd) != 0)
		perror("AbstractSocket::~AbstractSocket(): Closing socket");
	if (pthread_mutex_destroy(&_mutex) != 0)
		perror("AbstractSocket::~AbstractSocket(): Destroying mutex");
}

/**
 * Bind the socket to a given port.
 */
bool AbstractSocket::bind(unsigned short port)
{
	sockaddr_in inaddr;

	// Clear and set inet address/port.
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = INADDR_ANY;
	inaddr.sin_port = htons(port);

	// Perform binding.
	if (::bind(_sockfd, (struct sockaddr *)&inaddr, sizeof(inaddr)) != 0) {
		perror("AbstractSocket::bind()");
		return false;
	}

	return true;
}

/**
 * Connect to a host.
 *
 * \return
 * True on success, false on failure.
 */
bool AbstractSocket::connect(const HostAddress &addr,
		unsigned short port)
{
	sockaddr_in inaddr;

	// Clear and set address/port.
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = addr.toInetAddr();
	inaddr.sin_port = htons(port);

	// Perform connection.
	if (::connect(_sockfd, (struct sockaddr *)&inaddr, sizeof(inaddr)) != 0) {
		perror("AbstractSocket::connect()");
		return false;
	}

	return true;
}

/**
 * Shutdown the socket.
 *
 * \return
 * True on success, false on failure.
 */
bool AbstractSocket::shutdown()
{
	if (::shutdown(_sockfd, SHUT_RDWR) != 0) {
		perror("AbstractSocket::shutdown()");
		return false;
	}
	return true;
}

/**
 * Read a message.
 *
 * \return
 * Size read. On error, return -1.
 */
ssize_t AbstractSocket::read(char *buf, size_t size)
{
	ssize_t result;
	if ((result = ::read(_sockfd, buf, size)) < 0)
		perror("AbstractSocket::read()");
	return result;
}

/**
 * Write a message.
 *
 * \return
 * Size written. On error, return -1.
 */
ssize_t AbstractSocket::write(const char *buf, size_t size)
{
	ssize_t result;
	pthread_mutex_lock(&_mutex);
	if ((result = ::write(_sockfd, buf, size)) < 0)
		perror("AbstractSocket::write()");
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
		perror("AbstractSocket::setBlockable(): Getting flags");
		return false;
	}

	// Change arg.
	if (nonblk)
		arg |= O_NONBLOCK;
	else
		arg &= (~O_NONBLOCK);

	// Set arg.
	if ((fcntl(_sockfd, F_SETFL, arg)) < 0) {
		perror("AbstractSocket::setBlockable(): Setting flags");
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
		perror("AbstractSocket::setBlockable(): Getting flags");
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
		fprintf(stderr, "AbstractSocket::setTTL(): Error: TTL must greater or equal to 1.\n");
		return false;
	}
	if (setsockopt(_sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0) {
		perror("AbstractSocket::setTTL()");
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
		perror("AbstractSocket::TTL()");
		return -1;
	}
	return ttl;
}

/**
 * Get host address by host name (e.g. "www.google.com").
 */
HostAddress AbstractSocket::getHostByName(const string &host)
{
	struct hostent *phe;

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
unsigned short AbstractSocket::getServiceByName(const string &service)
{
	struct servent *pse;

	if ((pse = getservbyname(service.c_str(), NULL))) {
		return pse->s_port;
	}
	return 0;
}

}
