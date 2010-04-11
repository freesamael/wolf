#ifndef SOCKET_H_
#define SOCKET_H_

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
	AbstractSocket(int sock);
	virtual ~AbstractSocket();

	bool open();
	bool activeOpen(const HostAddress &addr, unsigned short port);
	bool passiveOpen(unsigned short port, int qlen = 10);
	bool close();
	ssize_t read(char *buf, size_t size);
	ssize_t write(const char *buf, size_t size);

	bool setNonblock(bool nonblk);
	bool isNonblock() const;
	bool setTTL(int ttl);
	int TTL() const;

	inline void changeState(ISocketState *state) { _state = state; }
	inline const ISocketState* state() const { return _state; }
	inline void setSockfd(int sock) { _sockfd = sock; }
	inline int sockfd() const { return _sockfd; }

	// Static helpers.
	static HostAddress getHostByName(const std::string &host);
	static unsigned short getServiceByName(const std::string &service);

protected:
	int _sockfd;
	pthread_mutex_t _mutex;
	ISocketState *_state;
};

}

#endif /* SOCKET_H_ */
