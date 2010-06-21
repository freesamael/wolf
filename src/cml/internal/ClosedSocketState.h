/**
 * \file ClosedSocketState.h
 * \date Apr 5, 2010
 * \author samael
 */

#ifndef CLOSEDSOCKETSTATE_H_
#define CLOSEDSOCKETSTATE_H_

#include <iostream>
#include <sstream>
#include <vector>
#include "ISocketState.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * ClosedSocketState implements closed state.
 *
 * \see ISocketState
 */
class ClosedSocketState: public ISocketState
{
	SINGLETON(ClosedSocketState);
public:
	inline const std::string& name() const { return _statestr; }

	bool open(AbstractSocket *sock);
	bool activeOpen(AbstractSocket *sock, const HostAddress &addr,
				uint16_t port);
	bool passiveOpen(AbstractSocket *sock, uint16_t port,	int qlen = 10);

	/// Unsupported operation with dummy implementation.
	inline bool close(AbstractSocket *UNUSED(sock)) { return false; }
	/// Unsupported operation with dummy implementation.
	inline TCPSocket* accept(AbstractSocket *UNUSED(sock)) { return NULL; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t read(AbstractSocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size)) { return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t write(AbstractSocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size)) { return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t recvfrom(AbstractSocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size), HostAddress *UNUSED(addr),
			uint16_t *UNUSED(port)) { return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t sendto(AbstractSocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size), const HostAddress &UNUSED(addr),
			uint16_t UNUSED(port)) { return -1; }

private:
	ClosedSocketState(): SINGLETON_MEMBER_INITLST, _statestr("Closed") {}
	bool _initialize(AbstractSocket *sock);
	std::string _statestr;
};

}

#endif /* CLOSEDSOCKETSTATE_H_ */
