/*
 * BoundSocketState.h
 *
 *  Created on: Apr 5, 2010
 *      Author: samael
 */

#ifndef BOUNDSOCKETSTATE_H_
#define BOUNDSOCKETSTATE_H_

#include "ISocketState.h"

namespace cml
{

class BoundSocketState: public ISocketState
{
public:
	static BoundSocketState* instance();
	static void release();
	inline const std::string& name() const { return _statestr; }

	// Supported operations.
	bool close(AbstractSocket *sock);
	TCPSocket* accept(AbstractSocket *sock);
	ssize_t recvfrom(AbstractSocket *sock, char *buf, size_t size,
			HostAddress *addr, unsigned short *port);
	ssize_t sendto(AbstractSocket *sock, const char *buf, size_t size,
			const HostAddress &addr, unsigned short port);

	// Unsupported operations.
	inline bool open(AbstractSocket *sock) { return false; }
	inline bool activeOpen(AbstractSocket *sock, const HostAddress &addr,
				unsigned short port) { return false; }
	inline bool passiveOpen(AbstractSocket *sock, unsigned short port,
			int qlen = 10) { return false; }
	inline ssize_t read(AbstractSocket *sock, char *buf, size_t size)
			{ return -1; }
	inline ssize_t write(AbstractSocket *sock, const char *buf, size_t size)
			{ return -1; }



private:
	BoundSocketState(): _statestr("Bound") {}
	static BoundSocketState *_instance;
	std::string _statestr;
};

}

#endif /* BOUNDSOCKETSTATE_H_ */
