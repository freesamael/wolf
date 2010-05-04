/**
 * \file SimpleActiveSocketState.h
 * \date Apr 6, 2010
 * \author samael
 */

#ifndef SIMPLEACTIVESOCKETSTATE_H_
#define SIMPLEACTIVESOCKETSTATE_H_

#include <vector>
#include <iostream>
#include "ISocketState.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * SimpleActiveSocketState implements active state.
 *
 * \see ISocketState
 */
class SimpleActiveSocketState: public ISocketState
{
	SINGLETON(SimpleActiveSocketState);
public:
	inline const std::string& name() const { return _statestr; }

	bool activeOpen(AbstractSocket *sock, const HostAddress &addr,
			uint16_t port);
	bool passiveOpen(AbstractSocket *sock, uint16_t port,
			int qlen = 10);
	bool close(AbstractSocket *sock);
	ssize_t sendto(AbstractSocket *sock, const char *buf, size_t size,
			const HostAddress &addr, uint16_t port);
	ssize_t recvfrom(AbstractSocket *sock, char *buf, size_t size,
			HostAddress *addr, uint16_t *port);

	/// Unsupported operation with dummy implementation.
	inline bool open(AbstractSocket *UNUSED(sock)) { return false; }
	/// Unsupported operation with dummy implementation.
	inline TCPSocket* accept(AbstractSocket *UNUSED(sock)) { return NULL; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t read(AbstractSocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size)) { return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t write(AbstractSocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size)) { return -1; }

private:
	SimpleActiveSocketState(): SINGLETON_MEMBER_INITLST, _statestr("Active") {}
	std::string _statestr;
};

}

#endif /* SIMPLEACTIVESOCKETSTATE_H_ */
