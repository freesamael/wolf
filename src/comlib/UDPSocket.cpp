/*
 * UDPSocket.cpp
 *
 *  Created on: Mar 8, 2010
 *      Author: samael
 */

#include <cstdio>
#include <cstring>
#include <errno.h>
#include "UDPSocket.h"

namespace cml
{

/**
 * Receive a UDP message from socket.
 *
 * \param[in] buf Buffer to write the incoming message.
 * \param[in] size Size of bytes to read.
 * \param[out] addr Sender address of incoming message.
 * \param[out] port Sender port of incoming message.
 *
 * \return
 * Size read. On error, return -1.
 *
 * \note
 * If the buffer size is not enough to record incoming message, the extra data
 * is discarded.
 */
ssize_t UDPSocket::recvfrom(char *buf, size_t size, HostAddress *addr,
		unsigned short *port)
{
	return _state->recvfrom(this, buf, size, addr, port);
}

/**
 * Send a UDP message to given address/port.
 *
 * \return
 * Size written. On error, return -1.
 */
ssize_t UDPSocket::sendto(const char *buf, size_t size, const HostAddress &addr,
		unsigned short port)
{
	pthread_mutex_lock(&_mutex);
	ssize_t result = _state->sendto(this, buf, size, addr, port);
	pthread_mutex_unlock(&_mutex);
	return result;
}

/**
 * Set if the it can broadcast.
 *
 * \return
 * True on success, false on failure.
 */
bool UDPSocket::setBroadcast(bool bcast)
{
	int broadcast = (bcast) ? 1 : 0;
	if (setsockopt(_sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
			sizeof(broadcast)) < 0) {
		perror("UDPSocket::setBroadcast()");
		return false;
	}
	return true;
}

/**
 * Check if it can broadcast.
 *
 * \return
 * True if it can, false if it can't or an error occurred.
 */
bool UDPSocket::canBroadcast() const
{
	int broadcast;
	socklen_t len = sizeof(broadcast);
	if (getsockopt(_sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, &len) < 0) {
		perror("UDPSocket::canBroadcast()");
		return false;
	}
	return broadcast;
}

}
