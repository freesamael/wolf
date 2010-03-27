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

AbstractSocket::~AbstractSocket()
{
	if (close() != 0)
		perror("AbstractSocket::~AbstractSocket: Closing socket");
	if (pthread_mutex_destroy(&_mutex) != 0)
		perror("AbstractSocket::~AbstractSocket: Destroying mutex");
}

/**
 * @brief Bind socket to a port.
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
 * @brief Connect to a host.
 * @return True on success, false on failure.
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
 * @brief Close the socket.
 * @return True on success, false on failure.
 */
bool AbstractSocket::close()
{
	if (::close(_sockfd) != 0) {
		perror("AbstractSocket::close()");
		return false;
	}
	return true;
}

/**
 * @brief Read a message.
 * @return Size read. On error, return -1.
 */
int AbstractSocket::read(char *buf, size_t size)
{
	int result;
	pthread_mutex_lock(&_mutex);
	if ((result = ::read(_sockfd, buf, size)) < 0)
		perror("AbstractSocket::read()");
	pthread_mutex_unlock(&_mutex);
	return result;
}

/**
 * @brief Write a message.
 * @return Size written. On error, return -1.
 */
int AbstractSocket::write(char *buf, size_t size)
{
	int result;
	pthread_mutex_lock(&_mutex);
	if ((result = ::write(_sockfd, buf, size)) < 0)
		perror("AbstractSocket::write()");
	pthread_mutex_unlock(&_mutex);
	return result;
}

/**
 * @brief Set if the socket is block or nonblock.
 * @details If the original flag is the same as the input argument, it does
 * nothing but return success.
 * @return True on success, false on failure.
 */
bool AbstractSocket::setBlockable(Blockable blk)
{
	int arg, narg;

	// Get arg.
	if ((arg = fcntl(_sockfd, F_GETFD, NULL)) < 0) {
		perror("AbstractSocket::setBlockable(): Getting flags");
		return false;
	}

	// Change arg.
	if (blk == NONBLOCK)
		narg = arg | O_NONBLOCK;
	else
		narg = arg & O_NONBLOCK;

	// Set arg.
	if (narg != arg) {
		if ((fcntl(_sockfd, F_SETFD, arg)) < 0) {
			perror("AbstractSocket::setBlockable(): Setting flags");
			return false;
		}
	}
	return true;
}

/**
 * @brief Get host address by host name (e.g. "www.google.com").
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
 * @brief Get port number by service name (e.g. "http").
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
