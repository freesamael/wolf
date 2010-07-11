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

namespace cml
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
	inline const std::string& name() const throw() { return _statestr; }

	void close(ASocket *sock) throw(XSocket);
	CTcpSocket* accept(ASocket *sock) throw(XSocket);
	ssize_t recvfrom(ASocket *sock, char *buf, size_t size,
			CHostAddress *addr, uint16_t *port) throw(XSocket);
	ssize_t sendto(ASocket *sock, const char *buf, size_t size,
			const CHostAddress &addr, uint16_t port) throw(XSocket);

	/// Unsupported operation.
	inline void open(ASocket *UNUSED(sock)) throw(XSocket)
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation.
	inline void activeOpen(ASocket *UNUSED(sock),
			const CHostAddress &UNUSED(addr), uint16_t UNUSED(port))
			throw(XSocket) { throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation.
	inline void passiveOpen(ASocket *UNUSED(sock), uint16_t UNUSED(port),
			int UNUSED(qlen), bool UNUSED(reuse)) throw(XSocket)
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation.
	inline ssize_t read(ASocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size)) throw(XSocket)
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation.
	inline ssize_t write(ASocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size)) throw(XSocket)
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }

private:
	CBoundSocketState(): SINGLETON_MEMBER_INITLST, _statestr("Bound") {}
	std::string _statestr;
};

}

#endif /* CBOUNDSOCKETSTATE_H_ */
