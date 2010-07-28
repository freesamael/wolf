/**
 * \file CBoundSocketState.h
 * \date Apr 5, 2010
 * \author: samael
 */

#ifndef CBOUNDSOCKETSTATE_H_
#define CBOUNDSOCKETSTATE_H_

#include <vector>
#include <iostream>
#include <sstream>
#include "ISocketState.h"
#include "HelperMacros.h"

namespace wolf
{

/**
 * CBoundSocketState implements bound state.
 *
 * \see ISocketState
 */
class CBoundSocketState: public ISocketState
{
	SINGLETON(CBoundSocketState);
public:
	inline const std::string& name() const  { return _statestr; }

	void close(ASocket *sock);
	int accept(ASocket *sock);
	ssize_t recvfrom(ASocket *sock, char *buf, size_t size,
			CHostAddress *addr, in_port_t *port);
	ssize_t sendto(ASocket *sock, const char *buf, size_t size,
			const CHostAddress &addr, in_port_t port);

	/// Unsupported operation.
	inline void open(ASocket *UNUSED(sock), SocketType UNUSED(type))
			 { throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation.
	inline void activeOpen(ASocket *UNUSED(sock), SocketType UNUSED(type),
			const CHostAddress &UNUSED(addr), in_port_t UNUSED(port))
			 { throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation.
	inline void passiveOpen(ASocket *UNUSED(sock), SocketType UNUSED(type),
			in_port_t UNUSED(port), int UNUSED(qlen), bool UNUSED(reuse))
			 { throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation.
	inline ssize_t read(ASocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size)) 
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation.
	inline ssize_t write(ASocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size)) 
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }

private:
	CBoundSocketState(): SINGLETON_MEMBER_INITLST, _statestr("Bound") {}
	std::string _statestr;
};

}

#endif /* CBOUNDSOCKETSTATE_H_ */
