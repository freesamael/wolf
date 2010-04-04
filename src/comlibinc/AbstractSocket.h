/*
 * Socket.h
 *
 *  Created on: Mar 8, 2010
 *      Author: samael
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <pthread.h>
#include "HostAddress.h"
#include "ITLVObject.h"

namespace cml
{

class AbstractSocket
{
public:
	typedef enum Blockable
	{
		BLOCK,
		NONBLOCK
	} Blockable;
	AbstractSocket();
	AbstractSocket(int sock);
	virtual ~AbstractSocket();
	virtual int type() const = 0;
	bool bind(unsigned short port);
	bool connect(const HostAddress &addr, unsigned short port);
	bool shutdown();
	bool close();
	ssize_t read(char *buf, size_t size);
	ssize_t write(const char *buf, size_t size);
	bool setBlockable(Blockable blk);
	bool setTTL(int ttl);
	int socketDescriptor() const { return _sockfd; }

	static HostAddress getHostByName(const std::string &host);
	static unsigned short getServiceByName(const std::string &service);

protected:
	int _sockfd;
	pthread_mutex_t _mutex;
};

}

#endif /* SOCKET_H_ */
