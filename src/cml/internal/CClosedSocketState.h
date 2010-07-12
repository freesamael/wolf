/**
 * \file CClosedSocketState.h
 * \date Apr 5, 2010
 * \author samael
 */

#ifndef CCLOSEDSOCKETSTATE_H_
#define CCLOSEDSOCKETSTATE_H_

#include <iostream>
#include <sstream>
#include <vector>
#include "ISocketState.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * CClosedSocketState implements closed state.
 *
 * \see ISocketState
 */
class CClosedSocketState: public ISocketState
{
	SINGLETON(CClosedSocketState);
public:
	inline const std::string& name() const throw() { return _statestr; }

	void open(ASocket *sock) throw(XSocket);
	void activeOpen(ASocket *sock, const CHostAddress &addr,
			in_port_t port) throw(XSocket);
	void passiveOpen(ASocket *sock, in_port_t port,	int qlen = 10,
			bool reuse = false) throw(XSocket);

	/// Unsupported operation.
	inline void close(ASocket *UNUSED(sock)) throw(XSocket)
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation with dummy implementation.
	inline CTcpSocket* accept(ASocket *UNUSED(sock)) throw(XSocket)
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation with dummy implementation.
	inline ssize_t read(ASocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size)) throw(XSocket)
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation with dummy implementation.
	inline ssize_t write(ASocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size)) throw(XSocket)
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation with dummy implementation.
	inline ssize_t recvfrom(ASocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size), CHostAddress *UNUSED(addr),
			in_port_t *UNUSED(port)) throw(XSocket)
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }
	/// Unsupported operation with dummy implementation.
	inline ssize_t sendto(ASocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size), const CHostAddress &UNUSED(addr),
			in_port_t UNUSED(port)) throw(XSocket)
			{ throw XSocket(XSocket::INVALID_SOCKET_STATE); }

private:
	CClosedSocketState(): SINGLETON_MEMBER_INITLST, _statestr("Closed") {}
	bool _initialize(ASocket *sock);
	std::string _statestr;
};

}

#endif /* CCLOSEDSOCKETSTATE_H_ */
