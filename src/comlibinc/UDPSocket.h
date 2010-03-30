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

class UDPSocket: public AbstractSocket
{
public:
	UDPSocket();
	UDPSocket(int sock): AbstractSocket(sock) {}
	inline int type() const { return SOCK_DGRAM; }
};

}

#endif /* UDPSOCKET_H_ */
