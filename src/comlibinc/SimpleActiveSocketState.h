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
 * Implements active state.
 *
 * \see ISocketState
 */
class SimpleActiveSocketState: public ISocketState
{
public:
	static SimpleActiveSocketState* instance();
	static void release();
	inline const std::string& name() const { return _statestr; }

	bool activeOpen(AbstractSocket *sock, const HostAddress &addr,
			unsigned short port);
	bool passiveOpen(AbstractSocket *sock, unsigned short port,
			int qlen = 10);
	bool close(AbstractSocket *sock);
	ssize_t sendto(AbstractSocket *sock, const char *buf, size_t size,
			const HostAddress &addr, unsigned short port);
	ssize_t recvfrom(AbstractSocket *sock, char *buf, size_t size,
			HostAddress *addr, unsigned short *port);

	/// Unsupported operation with dummy implementation.
	inline bool open(AbstractSocket *sock) { return false; }
	/// Unsupported operation with dummy implementation.
	inline TCPSocket* accept(AbstractSocket *sock) { return NULL; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t read(AbstractSocket *sock, char *buf, size_t size)
			{ return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t write(AbstractSocket *sock, const char *buf, size_t size)
			{ return -1; }

private:
	SimpleActiveSocketState(): _statestr("Active") {}
	static SimpleActiveSocketState *_instance;
	std::string _statestr;
};

}

#endif /* SIMPLEACTIVESOCKETSTATE_H_ */
