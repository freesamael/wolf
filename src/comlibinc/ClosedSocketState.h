/*
 * ClosedSocketState.h
 *
 *  Created on: Apr 5, 2010
 *      Author: samael
 */

#ifndef CLOSEDSOCKETSTATE_H_
#define CLOSEDSOCKETSTATE_H_

#include "ISocketState.h"

namespace cml
{

class ClosedSocketState: public ISocketState
{
public:
	static ClosedSocketState* instance();
	inline const std::string& toString() const { return _statestr; }

	// Supported operations.
	bool activeOpen(AbstractSocket *sock, const HostAddress &addr,
				unsigned short port);
	bool passiveOpen(AbstractSocket *sock, unsigned short port,	int qlen = 10);
	ssize_t sendto(AbstractSocket *sock, const char *buf, size_t size,
			const HostAddress &addr, unsigned short port);

	// Unsupported operations.
	inline bool close(AbstractSocket *sock) { return false; }
	inline TCPSocket* accept(AbstractSocket *sock) { return NULL; }
	inline ssize_t read(AbstractSocket *sock, char *buf, size_t size)
			{ return -1; }
	inline ssize_t write(AbstractSocket *sock, const char *buf, size_t size)
			{ return -1; }
	ssize_t recvfrom(AbstractSocket *sock, char *buf, size_t size,
			HostAddress *addr, unsigned short *port) { return -1; }

private:
	ClosedSocketState(): _statestr("Closed") {}
	bool _initialize(AbstractSocket *sock);
	static ClosedSocketState *_instance;
	std::string _statestr;
};

}

#endif /* CLOSEDSOCKETSTATE_H_ */
