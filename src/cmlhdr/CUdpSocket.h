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
	CUdpSocket() throw(XSocket, XThread) { open(); }
	CUdpSocket(int sock) throw(XSocket, XThread): ASocket(sock) {}
	inline void open() throw(XSocket)
			{ state()->open(this, ISocketState::UDP); }
	inline void activeOpen(const CHostAddress &addr, in_port_t port)
			throw(XSocket)
			{ state()->activeOpen(this, ISocketState::UDP, addr, port); }
	inline void passiveOpen(in_port_t port, int qlen = 10, bool reuse = false)
			throw(XSocket)
			{ state()->passiveOpen(this, ISocketState::UDP, port, qlen, reuse); }
	ssize_t recvfrom(char *buf, size_t size, CHostAddress *addr,
			in_port_t *port) throw(XSocket);
	ssize_t sendto(const char *buf, size_t size, const CHostAddress &addr,
			in_port_t port) throw(XSocket);
	void setBroadcast(bool bcast) throw(XSocket);
	bool canBroadcast() const throw(XSocket);
};

}

#endif /* CUDPSOCKET_H_ */
