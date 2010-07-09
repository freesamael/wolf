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
	inline const std::string& name() const { return _statestr; }

	bool open(ASocket *sock);
	bool activeOpen(ASocket *sock, const CHostAddress &addr,
				uint16_t port);
	bool passiveOpen(ASocket *sock, uint16_t port,	int qlen = 10);

	/// Unsupported operation with dummy implementation.
	inline bool close(ASocket *UNUSED(sock)) { return false; }
	/// Unsupported operation with dummy implementation.
	inline CTcpSocket* accept(ASocket *UNUSED(sock)) { return NULL; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t read(ASocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size)) { return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t write(ASocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size)) { return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t recvfrom(ASocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size), CHostAddress *UNUSED(addr),
			uint16_t *UNUSED(port)) { return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t sendto(ASocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size), const CHostAddress &UNUSED(addr),
			uint16_t UNUSED(port)) { return -1; }

private:
	CClosedSocketState(): SINGLETON_MEMBER_INITLST, _statestr("Closed") {}
	bool _initialize(ASocket *sock);
	std::string _statestr;
};

}

#endif /* CCLOSEDSOCKETSTATE_H_ */
