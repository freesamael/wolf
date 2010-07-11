/**
 * \file CConnectedSocketState.h
 * \date Apr 5, 2010
 * \author samael
 */

#ifndef CCONNECTEDSOCKETSTATE_H_
#define CCONNECTEDSOCKETSTATE_H_

#include <iostream>
#include <sstream>
#include <vector>
#include "ISocketState.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * CConnectedSocketState implements connected state.
 *
 * \see ISocketState
 */
class CConnectedSocketState: public ISocketState
{
	SINGLETON(CConnectedSocketState);
public:
	inline const std::string& name() const throw() { return _statestr; }

	void close(ASocket *sock) throw(XSocket);
	ssize_t read(ASocket *sock, char *buf, size_t size) throw(XSocket);
	ssize_t write(ASocket *sock, const char *buf, size_t size) throw(XSocket);

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
	inline CTcpSocket* accept(ASocket *UNUSED(sock)) throw(XSocket)
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation.
	inline ssize_t recvfrom(ASocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size), CHostAddress *UNUSED(addr),
			uint16_t *UNUSED(port)) throw(XSocket)
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation.
	inline ssize_t sendto(ASocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size), const CHostAddress &UNUSED(addr),
			uint16_t UNUSED(port)) throw(XSocket)
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }

private:
	CConnectedSocketState(): SINGLETON_MEMBER_INITLST, _statestr("Connected") {}
	std::string _statestr;
};

}

#endif /* CCONNECTEDSOCKETSTATE_H_ */
