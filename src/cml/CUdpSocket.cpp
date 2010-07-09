/**
 * \file CUdpSocket.cpp
 * \date Mar 8, 2010
 * \author samael
 */

#include <cstdio>
#include <cstring>
#include <errno.h>
#include "CUdpSocket.h"

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
ssize_t CUdpSocket::recvfrom(char *buf, size_t size, CHostAddress *addr,
		uint16_t *port)
{
	return _state->recvfrom(this, buf, size, addr, port);
}

/**
 * Send a UDP message to given address/port.
 *
 * \return
 * Size written. On error, return -1.
 */
ssize_t CUdpSocket::sendto(const char *buf, size_t size, const CHostAddress &addr,
		uint16_t port)
{
	return _state->sendto(this, buf, size, addr, port);;
}

/**
 * Set if the it can broadcast.
 *
 * \return
 * True on success, false on failure.
 */
bool CUdpSocket::setBroadcast(bool bcast)
{
	int broadcast = (bcast) ? 1 : 0;
	if (setsockopt(_sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
			sizeof(broadcast)) < 0) {
		perror("Error: UDPSocket::setBroadcast()");
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
bool CUdpSocket::canBroadcast() const
{
	int broadcast;
	socklen_t len = sizeof(broadcast);
	if (getsockopt(_sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, &len) < 0) {
		perror("Error: UDPSocket::canBroadcast()");
		return false;
	}
	return broadcast;
}

}
