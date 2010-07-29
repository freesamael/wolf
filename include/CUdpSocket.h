/**
 * \file CUdpSocket.h
 * \date Mar 8, 2010
 * \author samael
 */

#ifndef CUDPSOCKET_H_
#define CUDPSOCKET_H_

#include "ASocket.h"

namespace wolf
{

/**
 * It represents UDP sockets.
 *
 * \see AbstractSocket
 */
class CUdpSocket: public ASocket
{
public:
	CUdpSocket()  { open(); }
	CUdpSocket(int sock) : ASocket(sock) {}
	inline void open() 
			{ state()->open(this, ISocketState::UDP); }
	inline void activeOpen(const CHostAddress &addr, in_port_t port)
			
			{ state()->activeOpen(this, ISocketState::UDP, addr, port); }
	inline void passiveOpen(in_port_t port, int qlen = 10, bool reuse = false)
			
			{ state()->passiveOpen(this, ISocketState::UDP, port, qlen, reuse); }
	ssize_t recvfrom(char *buf, size_t size, CHostAddress *addr,
			in_port_t *port) ;
	ssize_t sendto(const char *buf, size_t size, const CHostAddress &addr,
			in_port_t port) ;
	void setBroadcast(bool bcast) ;
	bool canBroadcast() const ;
};

}

#endif /* CUDPSOCKET_H_ */
