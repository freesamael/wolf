/**
 * \file ClosedSocketState.h
 * \date Apr 5, 2010
 * \author samael
 */

#ifndef CLOSEDSOCKETSTATE_H_
#define CLOSEDSOCKETSTATE_H_

#include "ISocketState.h"

namespace cml
{

/**
 * ClosedSocketState implements closed state.
 *
 * \see ISocketState
 */
class ClosedSocketState: public ISocketState
{
public:
	static ClosedSocketState* instance();
	static void release();
	inline const std::string& name() const { return _statestr; }

	bool open(AbstractSocket *sock);
	bool activeOpen(AbstractSocket *sock, const HostAddress &addr,
				unsigned short port);
	bool passiveOpen(AbstractSocket *sock, unsigned short port,	int qlen = 10);

	/// Unsupported operation with dummy implementation.
	inline bool close(AbstractSocket *sock) { return false; }
	/// Unsupported operation with dummy implementation.
	inline TCPSocket* accept(AbstractSocket *sock) { return NULL; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t read(AbstractSocket *sock, char *buf, size_t size)
			{ return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t write(AbstractSocket *sock, const char *buf, size_t size)
			{ return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t recvfrom(AbstractSocket *sock, char *buf, size_t size,
			HostAddress *addr, unsigned short *port) { return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t sendto(AbstractSocket *sock, const char *buf, size_t size,
			const HostAddress &addr, unsigned short port) { return -1; }

private:
	ClosedSocketState(): _statestr("Closed") {}
	bool _initialize(AbstractSocket *sock);
	static ClosedSocketState *_instance;
	std::string _statestr;
};

}

#endif /* CLOSEDSOCKETSTATE_H_ */
