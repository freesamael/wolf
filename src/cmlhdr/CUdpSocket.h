/**
 * \file CUdpSocket.h
 * \date Mar 8, 2010
 * \author samael
 */

#ifndef CUDPSOCKET_H_
#define CUDPSOCKET_H_

#include "ASocket.h"

namespace cml
{

/**
 * It represents UDP sockets.
 *
 * \see AbstractSocket
 */
class CUdpSocket: public ASocket
{
public:
	CUdpSocket() { open(); }
	CUdpSocket(int sock): ASocket(sock) {}
	ssize_t recvfrom(char *buf, size_t size, CHostAddress *addr,
			uint16_t *port);
	ssize_t sendto(const char *buf, size_t size, const CHostAddress &addr,
			uint16_t port);
	bool setBroadcast(bool bcast);
	bool canBroadcast() const;
};

}

#endif /* CUDPSOCKET_H_ */
