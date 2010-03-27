/*
 * TCPServer.cpp
 *
 *  Created on: Mar 8, 2010
 *      Author: samael
 */

#include <cstdio>
#include <errno.h>
#include "TCPServer.h"
#include "Thread.h"

using namespace std;

namespace cml
{

TCPServer::~TCPServer()
{
	for (unsigned i = 0; i < _socks.size(); i++)
		delete _socks[i];
}

/**
 * @brief Listen with queue lenth = qlen.
 */
bool TCPServer::listen(unsigned qlen)
{
	if (::listen(_sockfd, qlen) < 0) {
		perror("TCPServer::listen()");
		return false;
	}
	return true;
}

/**
 * @brief Overloaded function which combines bind() and listen().
 */
bool TCPServer::listen(unsigned short port, unsigned qlen)
{
	if (bind(port))
		if (listen(qlen))
			return true;
	return false;
}

/**
 * @brief Accept for incoming connections.
 * @details If set with NONBLOCK and no pending requests, it returns NULL. If
 * set with BLOCK, it will block waiting until a request is pended.
 * @return A pointer to TCPSocket representing incoming connection if success,
 * NULL if failure. Note that the TCPSocket is managed by TCPServer and should
 * not be delete/free manually. TCPServer handles this.
 */
TCPSocket* TCPServer::accept(AbstractSocket::Blockable blk)
{
	if (setBlockable(blk)) {
		struct sockaddr_in inaddr;
		unsigned addlen = sizeof(inaddr);
		int sock;

		if ((sock = ::accept(_sockfd, (struct sockaddr *)&inaddr,
				&addlen)) < 0) {
			perror("TCPServer::accept()");
			return NULL;
		}
		TCPSocket *tcpsock = new TCPSocket(sock);
		_socks.push_back(tcpsock);
		return tcpsock;
	}
	return NULL;
}

}
