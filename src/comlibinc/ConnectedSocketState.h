/*
 * ConnectedSocketState.h
 *
 *  Created on: Apr 5, 2010
 *      Author: samael
 */

#ifndef CONNECTEDSOCKETSTATE_H_
#define CONNECTEDSOCKETSTATE_H_

#include "ISocketState.h"

namespace cml
{

class ConnectedSocketState: public ISocketState
{
public:
	static ConnectedSocketState* instance();
	static void release();
	inline const std::string& name() const { return _statestr; }

	// Supported operations.
	bool close(AbstractSocket *sock);
	ssize_t read(AbstractSocket *sock, char *buf, size_t size);
	ssize_t write(AbstractSocket *sock, const char *buf, size_t size);

	// Unsupported operations.
	inline bool open(AbstractSocket *sock) { return false; }
	inline bool activeOpen(AbstractSocket *sock, const HostAddress &addr,
				unsigned short port) { return false; }
	inline bool passiveOpen(AbstractSocket *sock, unsigned short port,
			int qlen = 10) { return false; }
	inline TCPSocket* accept(AbstractSocket *sock) { return NULL; }
	inline ssize_t recvfrom(AbstractSocket *sock, char *buf, size_t size,
			HostAddress *addr, unsigned short *port) { return -1; }
	inline ssize_t sendto(AbstractSocket *sock, const char *buf, size_t size,
			const HostAddress &addr, unsigned short port) { return -1; }


private:
	ConnectedSocketState(): _statestr("Connected") {}
	static ConnectedSocketState *_instance;
	std::string _statestr;
};

}

#endif /* CONNECTEDSOCKETSTATE_H_ */
