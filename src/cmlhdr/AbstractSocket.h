/**
 * \file AbstractSocket.h
 * \date Mar 8, 2010
 * \author samael
 */

#ifndef ABSTRACTSOCKET_H_
#define ABSTRACTSOCKET_H_

#include <iostream>
#include <sstream>
#include <string>
#include <stdint.h>
#include "HostAddress.h"
#include "ITLVObject.h"
#include "ISocketState.h"
#include "Mutex.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * The abstract socket used for TCP/UDP sockets. It encapsulates the underlying
 * socket states by ISocketState.
 */
class AbstractSocket
{
public:
	static const std::string ClosedState;
	static const std::string ActiveState;
	static const std::string BoundState;
	static const std::string ConnectedState;

	AbstractSocket();
	AbstractSocket(const AbstractSocket &sock);
	AbstractSocket(int sockfd);
	virtual ~AbstractSocket();
	AbstractSocket& operator=(const AbstractSocket &sock);

	bool open();
	bool activeOpen(const HostAddress &addr, uint16_t port);
	bool passiveOpen(uint16_t port, int qlen = 10);
	bool close();

	inline bool lockread() { PINF_3("Lock read."); return _rmx.lock(); }
	inline bool unlockread() { PINF_3("Unlock read."); return _rmx.unlock(); }
	inline bool lockwrite() { PINF_3("Lock write."); return _wmx.lock(); }
	inline bool unlockwrite() { PINF_3("Unlock write."); return _wmx.unlock(); }
	ssize_t read(char *buf, size_t size);
	ssize_t write(const char *buf, size_t size);

	bool setNonblock(bool nonblk);
	bool isNonblock() const;
	bool setTTL(int ttl);
	int TTL() const;
	HostAddress currentAddress() const;
	HostAddress peerAddress() const;

	inline void changeState(ISocketState *state) { _state = state; }
	inline const ISocketState* state() const { return _state; }
	inline void setSockfd(int sockfd) { _sockfd = sockfd; }
	inline int sockfd() const { return _sockfd; }

	// Static helpers.
	static void registerSocketDependant(void (*rls)());

protected:
	int _sockfd;
	Mutex _wmx, _rmx;
	ISocketState *_state;
};

}

#endif /* ABSTRACTSOCKET_H_ */
