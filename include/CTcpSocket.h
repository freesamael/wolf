/**
 * \file CTcpSocket.h
 * \date Mar 8, 2010
 * \author samael
 */

#ifndef CTCPSOCKET_H_
#define CTCPSOCKET_H_

#include <vector>
#include "ASocket.h"
#include "HelperMacros.h"

namespace wolf
{

/**
 * CTcpSocket represents TCP sockets. If a CTcpSocket is created by accept(),
 * it's managed by the master socket who creates it, and the master socket will
 * destroy it on destruction of the master socket. You can use
 * setAutoclean(false) to explicitly avoid master socket deleting slaves
 * automatically.
 *
 * \see ASocket
 */
class CTcpSocket: public ASocket
{
public:
	CTcpSocket() throw(XSocket, XThread) {}
	CTcpSocket(int sock) throw(XSocket, XThread): ASocket(sock) {}
	virtual ~CTcpSocket() throw() {}
	inline void open() throw(XSocket)
			{ state()->open(this, ISocketState::TCP); }
	inline void activeOpen(const CHostAddress &addr, in_port_t port)
			throw(XSocket)
			{ state()->activeOpen(this, ISocketState::TCP, addr, port); }
	inline void passiveOpen(in_port_t UNUSED(port), int UNUSED(qlen) = 10,
			bool UNUSED(reuse) = false) throw(XSocket)
			{ throw XSocket(__PRETTY_FUNCTION__, __LINE__,
					XSocket::INVALID_SOCKET_TYPE); }
};

}

#endif /* CTCPSOCKET_H_ */
