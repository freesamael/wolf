/**
 * \file BoundSocketState.h
 * \date Apr 5, 2010
 * \author: samael
 */

#ifndef BOUNDSOCKETSTATE_H_
#define BOUNDSOCKETSTATE_H_

#include <vector>
#include <iostream>
#include "ISocketState.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * BoundSocketState implements bound state.
 *
 * \see ISocketState
 */
class BoundSocketState: public ISocketState
{
	SINGLETON(BoundSocketState);
public:
	inline const std::string& name() const { return _statestr; }

	bool close(AbstractSocket *sock);
	TCPSocket* accept(AbstractSocket *sock);
	ssize_t recvfrom(AbstractSocket *sock, char *buf, size_t size,
			HostAddress *addr, uint16_t *port);
	ssize_t sendto(AbstractSocket *sock, const char *buf, size_t size,
			const HostAddress &addr, uint16_t port);

	/// Unsupported operation with dummy implementation.
	inline bool open(AbstractSocket *sock) { return false; }
	/// Unsupported operation with dummy implementation.
	inline bool activeOpen(AbstractSocket *sock, const HostAddress &addr,
				uint16_t port) { return false; }
	/// Unsupported operation with dummy implementation.
	inline bool passiveOpen(AbstractSocket *sock, uint16_t port,
			int qlen = 10) { return false; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t read(AbstractSocket *sock, char *buf, size_t size)
			{ return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t write(AbstractSocket *sock, const char *buf, size_t size)
			{ return -1; }



private:
	BoundSocketState(): _statestr("Bound") {}
	std::string _statestr;
};

}

#endif /* BOUNDSOCKETSTATE_H_ */