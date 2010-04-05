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

UDPSocket::UDPSocket()
{
	if ((_sockfd = socket(AF_INET, type(), 0)) < 0)
		perror("UDPSocket::UDPSocket()");
}

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
	ssize_t result;
	struct sockaddr_in inaddr;
	socklen_t alen = sizeof(inaddr);

	if ((result = ::recvfrom(_sockfd, buf, size, 0,
			(struct sockaddr *)&inaddr, &alen)) < 0) {
		perror("UDPSocket::recvfrom()");
	}

	addr->setAddr(inaddr.sin_addr.s_addr);
	*port = ntohs(inaddr.sin_port);

	return result;
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
	ssize_t result;
	sockaddr_in inaddr;

	// Clear and set address/port.
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = addr.toInetAddr();
	inaddr.sin_port = htons(port);

	pthread_mutex_lock(&_mutex);
	if ((result = ::sendto(_sockfd, buf, size, 0, (struct sockaddr *)&inaddr,
			sizeof(inaddr))) < 0) {
		perror("UDPSocket::sendto()");
	}
	pthread_mutex_unlock(&_mutex);

	return result;
}

/**
 * Set if the it can broadcast.
 * \return
 * True on success, false on failure.
 */
bool UDPSocket::setBroadcast(bool bcast)
{
	int broadcast = (bcast) ? 1 : 0;
	if (setsockopt(_sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
			sizeof(broadcast)) < 0) {
		perror("UDPSocket::setBroadcast");
		return false;
	}
	return true;
}

}
