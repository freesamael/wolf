/*
 * SimpleActiveSocketState.h
 *
 *  Created on: Apr 6, 2010
 *      Author: samael
 */

#ifndef SIMPLEACTIVESOCKETSTATE_H_
#define SIMPLEACTIVESOCKETSTATE_H_

#include "ISocketState.h"

namespace cml
{

/**
 * Simple active state is only valid for UDP socket.
 */
class SimpleActiveSocketState: public ISocketState
{
public:
	static SimpleActiveSocketState* instance();
	inline const std::string& toString() const { return _statestr; }

	// Supported operations.
	bool activeOpen(AbstractSocket *sock, const HostAddress &addr,
			unsigned short port);
	bool passiveOpen(AbstractSocket *sock, unsigned short port,
			int qlen = 10);
	bool close(AbstractSocket *sock);
	ssize_t sendto(AbstractSocket *sock, const char *buf, size_t size,
			const HostAddress &addr, unsigned short port);

	// Unsupported operations.
	inline bool open(AbstractSocket *sock) { return false; }
	inline TCPSocket* accept(AbstractSocket *sock) { return NULL; }
	inline ssize_t read(AbstractSocket *sock, char *buf, size_t size)
			{ return -1; }
	inline ssize_t write(AbstractSocket *sock, const char *buf, size_t size)
			{ return -1; }
	inline ssize_t recvfrom(AbstractSocket *sock, char *buf, size_t size,
				HostAddress *addr, unsigned short *port) { return -1; }



private:
	SimpleActiveSocketState(): _statestr("Bound") {}
	static SimpleActiveSocketState *_instance;
	std::string _statestr;
};

}

#endif /* SIMPLEACTIVESOCKETSTATE_H_ */
