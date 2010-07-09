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

namespace cml
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
	inline const std::string& name() const { return _statestr; }

	bool activeOpen(ASocket *sock, const CHostAddress &addr,
			uint16_t port);
	bool passiveOpen(ASocket *sock, uint16_t port,
			int qlen = 10);
	bool close(ASocket *sock);
	ssize_t sendto(ASocket *sock, const char *buf, size_t size,
			const CHostAddress &addr, uint16_t port);
	ssize_t recvfrom(ASocket *sock, char *buf, size_t size,
			CHostAddress *addr, uint16_t *port);

	/// Unsupported operation with dummy implementation.
	inline bool open(ASocket *UNUSED(sock)) { return false; }
	/// Unsupported operation with dummy implementation.
	inline CTcpSocket* accept(ASocket *UNUSED(sock)) { return NULL; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t read(ASocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size)) { return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t write(ASocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size)) { return -1; }

private:
	CSimpleActiveSocketState(): SINGLETON_MEMBER_INITLST, _statestr("Active") {}
	std::string _statestr;
};

}

#endif /* CSIMPLEACTIVESOCKETSTATE_H_ */
