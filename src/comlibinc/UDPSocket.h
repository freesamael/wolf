/**
 * \file UDPSocket.h
 * \date Mar 8, 2010
 * \author samael
 */

#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

#include "AbstractSocket.h"

namespace cml
{

/**
 * It represents UDP sockets.
 *
 * \see AbstractSocket
 */
class UDPSocket: public AbstractSocket
{
public:
	UDPSocket() { open(); }
	UDPSocket(int sock): AbstractSocket(sock) {}
	ssize_t recvfrom(char *buf, size_t size, HostAddress *addr,
			unsigned short *port);
	ssize_t sendto(const char *buf, size_t size, const HostAddress &addr,
			unsigned short port);
	bool setBroadcast(bool bcast);
	bool canBroadcast() const;
};

}

#endif /* UDPSOCKET_H_ */
