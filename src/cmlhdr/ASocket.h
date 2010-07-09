/**
 * \file ASocket.h
 * \date Mar 8, 2010
 * \author samael
 */

#ifndef ASOCKET_H_
#define ASOCKET_H_

#include <iostream>
#include <sstream>
#include <string>
#include <stdint.h>
#include "CHostAddress.h"
#include "ITlvObject.h"
#include "ISocketState.h"
#include "CMutex.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * The abstract socket used for TCP/UDP sockets. It encapsulates the underlying
 * socket states by ISocketState.
 */
class ASocket
{
public:
	static const std::string ClosedState;
	static const std::string ActiveState;
	static const std::string BoundState;
	static const std::string ConnectedState;

	ASocket();
	ASocket(const ASocket &sock);
	ASocket(int sockfd);
	virtual ~ASocket();
	ASocket& operator=(const ASocket &sock);

	bool open();
	bool activeOpen(const CHostAddress &addr, uint16_t port);
	bool passiveOpen(uint16_t port, int qlen = 10);
	bool close();

	inline bool lockread() { PINF_3("Lock read."); return _rmx.lock(); }
	inline bool unlockread() { PINF_3("Unlock read."); return _rmx.unlock(); }
	bool lockwrite();
	bool unlockwrite();
	ssize_t read(char *buf, size_t size);
	ssize_t write(const char *buf, size_t size);

	bool setNonblock(bool nonblk);
	bool isNonblock() const;
	bool setTTL(int ttl);
	int TTL() const;
	CHostAddress currentAddress() const;
	CHostAddress peerAddress() const;

	inline void changeState(ISocketState *state) { _state = state; }
	inline const ISocketState* state() const { return _state; }
	inline void setSockfd(int sockfd) { _sockfd = sockfd; }
	inline int sockfd() const { return _sockfd; }

	// Static helpers.
	static void registerSocketDependant(void (*rls)());

protected:
	int _sockfd;
	CMutex _wmx, _rmx;
	ISocketState *_state;
};

}

#endif /* ASOCKET_H_ */
