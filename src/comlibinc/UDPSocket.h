/*
 * UDPSocket.h
 *
 *  Created on: Mar 8, 2010
 *      Author: samael
 */

#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

#include "AbstractSocket.h"

namespace cml
{

class HostAddress;
class UDPSocket: public AbstractSocket
{
public:
	UDPSocket();
	UDPSocket(int sock): AbstractSocket(sock) {}
	inline int type() const { return SOCK_DGRAM; }
	ssize_t recvfrom(char *buf, size_t size, HostAddress *addr,
			unsigned short *port);
	ssize_t sendto(const char *buf, size_t size, const HostAddress &addr,
			unsigned short port);
};

}

#endif /* UDPSOCKET_H_ */
