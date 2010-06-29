/**
 * \file ConnectedSocketState.h
 * \date Apr 5, 2010
 * \author samael
 */

#ifndef CONNECTEDSOCKETSTATE_H_
#define CONNECTEDSOCKETSTATE_H_

#include <iostream>
#include <sstream>
#include <vector>
#include "Mutex.h"
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
	inline Mutex& mutex() { return _mx; }

	bool close(AbstractSocket *sock);
	ssize_t read(AbstractSocket *sock, char *buf, size_t size);
	ssize_t write(AbstractSocket *sock, const char *buf, size_t size);

	/// Unsupported operation with dummy implementation.
	inline bool open(AbstractSocket *UNUSED(sock)) { return false; }
	/// Unsupported operation with dummy implementation.
	inline bool activeOpen(AbstractSocket *UNUSED(sock),
			const HostAddress &UNUSED(addr), uint16_t UNUSED(port))
			{ return false; }
	/// Unsupported operation with dummy implementation.
	inline bool passiveOpen(AbstractSocket *UNUSED(sock), uint16_t UNUSED(port),
			int UNUSED(qlen)) { return false; }
	/// Unsupported operation with dummy implementation.
	inline TCPSocket* accept(AbstractSocket *UNUSED(sock)) { return NULL; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t recvfrom(AbstractSocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size), HostAddress *UNUSED(addr),
			uint16_t *UNUSED(port)) { return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t sendto(AbstractSocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size), const HostAddress &UNUSED(addr),
			uint16_t UNUSED(port)) { return -1; }

private:
	ConnectedSocketState(): SINGLETON_MEMBER_INITLST, _statestr("Connected"),
		_mx() {}
	std::string _statestr;
	Mutex _mx;
};

}

#endif /* CONNECTEDSOCKETSTATE_H_ */
