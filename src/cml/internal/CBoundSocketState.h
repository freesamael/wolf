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
	inline const std::string& name() const { return _statestr; }

	bool close(ASocket *sock);
	CTcpSocket* accept(ASocket *sock);
	ssize_t recvfrom(ASocket *sock, char *buf, size_t size,
			CHostAddress *addr, uint16_t *port);
	ssize_t sendto(ASocket *sock, const char *buf, size_t size,
			const CHostAddress &addr, uint16_t port);

	/// Unsupported operation with dummy implementation.
	inline bool open(ASocket *UNUSED(sock)) { return false; }
	/// Unsupported operation with dummy implementation.
	inline bool activeOpen(ASocket *UNUSED(sock),
			const CHostAddress &UNUSED(addr), uint16_t UNUSED(port))
			{ return false; }
	/// Unsupported operation with dummy implementation.
	inline bool passiveOpen(ASocket *UNUSED(sock), uint16_t UNUSED(port),
			int UNUSED(qlen)) { return false; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t read(ASocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size)) { return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t write(ASocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size)) { return -1; }

private:
	CBoundSocketState(): SINGLETON_MEMBER_INITLST, _statestr("Bound") {}
	std::string _statestr;
};

}

#endif /* CBOUNDSOCKETSTATE_H_ */
