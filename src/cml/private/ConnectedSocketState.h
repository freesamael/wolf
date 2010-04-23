/**
 * \file ConnectedSocketState.h
 * \date Apr 5, 2010
 * \author samael
 */

#ifndef CONNECTEDSOCKETSTATE_H_
#define CONNECTEDSOCKETSTATE_H_

#include <vector>
#include <iostream>
#include "ISocketState.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * ConnectedSocketState implements connected state.
 *
 * \see ISocketState
 */
class ConnectedSocketState: public ISocketState
{
	SINGLETON(ConnectedSocketState);
public:
	inline const std::string& name() const { return _statestr; }

	bool close(AbstractSocket *sock);
	ssize_t read(AbstractSocket *sock, char *buf, size_t size);
	ssize_t write(AbstractSocket *sock, const char *buf, size_t size);

	/// Unsupported operation with dummy implementation.
	inline bool open(AbstractSocket *sock) { return false; }
	/// Unsupported operation with dummy implementation.
	inline bool activeOpen(AbstractSocket *sock, const HostAddress &addr,
				uint16_t port) { return false; }
	/// Unsupported operation with dummy implementation.
	inline bool passiveOpen(AbstractSocket *sock, uint16_t port,
			int qlen = 10) { return false; }
	/// Unsupported operation with dummy implementation.
	inline TCPSocket* accept(AbstractSocket *sock) { return NULL; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t recvfrom(AbstractSocket *sock, char *buf, size_t size,
			HostAddress *addr, uint16_t *port) { return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t sendto(AbstractSocket *sock, const char *buf, size_t size,
			const HostAddress &addr, uint16_t port) { return -1; }


private:
	ConnectedSocketState(): _statestr("Connected") {}
	std::string _statestr;
};

}

#endif /* CONNECTEDSOCKETSTATE_H_ */