/**
 * \file CUdpSocket.cpp
 * \date Mar 8, 2010
 * \author samael
 */

#include <errno.h>
#include <sys/socket.h>
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
 * Size read. Zero if the socket is non-blocking and no data to read.
 *
 * \note
 * If the buffer size is not enough to record incoming message, the extra data
 * is discarded.
 */
ssize_t CUdpSocket::recvfrom(char *buf, size_t size, CHostAddress *addr,
		in_port_t *port) throw(XSocket)
{
	return _state->recvfrom(this, buf, size, addr, port);
}

/**
 * Send a UDP message to given address/port.
 *
 * \return
 * Size written.
 */
ssize_t CUdpSocket::sendto(const char *buf, size_t size, const CHostAddress &addr,
		in_port_t port) throw(XSocket)
{
	return _state->sendto(this, buf, size, addr, port);;
}

/**
 * Set if the it can broadcast.
 */
void CUdpSocket::setBroadcast(bool bcast) throw(XSocket)
{
	int broadcast = (bcast) ? 1 : 0;
	if (setsockopt(_sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
			sizeof(broadcast)) != 0) {
		throw XSocket(errno);
	}
}

/**
 * Check if it can broadcast.
 *
 * \return
 * True if it can broadcast, false otherwise.
 */
bool CUdpSocket::canBroadcast() const throw(XSocket)
{
	int broadcast;
	socklen_t len = sizeof(broadcast);
	if (getsockopt(_sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, &len) != 0)
		throw XSocket(errno);
	return broadcast;
}

}
