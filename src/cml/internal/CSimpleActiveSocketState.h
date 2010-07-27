/**
 * \file CSimpleActiveSocketState.h
 * \date Apr 6, 2010
 * \author samael
 */

#ifndef CSIMPLEACTIVESOCKETSTATE_H_
#define CSIMPLEACTIVESOCKETSTATE_H_

#include <iostream>
#include <sstream>
#include <vector>
#include "ISocketState.h"
#include "HelperMacros.h"

namespace wolf
{

/**
 * CSimpleActiveSocketState implements active state.
 *
 * \see ISocketState
 */
class CSimpleActiveSocketState: public ISocketState
{
	SINGLETON(CSimpleActiveSocketState);
public:
	inline const std::string& name() const throw() { return _statestr; }

	void activeOpen(ASocket *sock, SocketType type, const CHostAddress &addr,
			in_port_t port) throw(XSocket);
	void passiveOpen(ASocket *sock, SocketType type, in_port_t port,
			int qlen = 10, bool reuse = false) throw(XSocket);
	void close(ASocket *sock) throw(XSocket);
	ssize_t sendto(ASocket *sock, const char *buf, size_t size,
			const CHostAddress &addr, in_port_t port) throw(XSocket);
	ssize_t recvfrom(ASocket *sock, char *buf, size_t size,
			CHostAddress *addr, in_port_t *port) throw(XSocket);

	/// Unsupported operation.
	inline void open(ASocket *UNUSED(sock), SocketType UNUSED(type))
			throw(XSocket) { throw XSocket(__PRETTY_FUNCTION__, __LINE__,
					XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation.
	inline int accept(ASocket *UNUSED(sock)) throw(XSocket)
			{ throw XSocket(__PRETTY_FUNCTION__, __LINE__,
					XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation.
	inline ssize_t read(ASocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size)) throw(XSocket)
			{ throw XSocket(__PRETTY_FUNCTION__, __LINE__,
					XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation.
	inline ssize_t write(ASocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size)) throw(XSocket)
			{ throw XSocket(__PRETTY_FUNCTION__, __LINE__,
					XSocket::INVALID_SOCKET_STATE); }

private:
	CSimpleActiveSocketState(): SINGLETON_MEMBER_INITLST, _statestr("Active") {}
	std::string _statestr;
};

}

#endif /* CSIMPLEACTIVESOCKETSTATE_H_ */
