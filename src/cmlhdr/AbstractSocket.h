/**
 * \file AbstractSocket.h
 * \date Mar 8, 2010
 * \author samael
 */

#ifndef ABSTRACTSOCKET_H_
#define ABSTRACTSOCKET_H_

#include <stdint.h>
#include <pthread.h>
#include "HostAddress.h"
#include "ITLVObject.h"
#include "ISocketState.h"

namespace cml
{

/**
 * The abstract socket used for TCP/UDP sockets. It encapsulates the underlying
 * socket states by ISocketState.
 */
class AbstractSocket
{
public:
	AbstractSocket();
	AbstractSocket(const AbstractSocket &sock);
	AbstractSocket(int sock);
	virtual ~AbstractSocket();
	AbstractSocket& operator=(const AbstractSocket &sock);

	bool open();
	bool activeOpen(const HostAddress &addr, uint16_t port);
	bool passiveOpen(uint16_t port, int qlen = 10);
	bool close();
	ssize_t read(char *buf, size_t size);
	ssize_t write(const char *buf, size_t size);

	bool setNonblock(bool nonblk);
	bool isNonblock() const;
	bool setTTL(int ttl);
	int TTL() const;
	HostAddress currentAddress() const;

	inline void changeState(ISocketState *state) { _state = state; }
	inline const ISocketState* state() const { return _state; }
	inline void setSockfd(int sock) { _sockfd = sock; }
	inline int sockfd() const { return _sockfd; }

	// Static helpers.
	static HostAddress getHostByName(const std::string &host);
	static uint16_t getServiceByName(const std::string &service);
	static void registerSocketDependant(void (*rls)());

protected:
	int _sockfd;
	pthread_mutex_t _mutex;
	ISocketState *_state;
};

}

#endif /* ABSTRACTSOCKET_H_ */
