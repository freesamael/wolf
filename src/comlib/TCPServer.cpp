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
 * \internal
 * Listen with queue lenth = qlen.
 */
bool TCPServer::_listen(unsigned qlen)
{
	if (::listen(_sockfd, qlen) < 0) {
		perror("TCPServer::listen()");
		return false;
	}
	return true;
}

/**
 * Overloaded function which combines bind() and listen().
 */
bool TCPServer::listen(unsigned short port, unsigned qlen)
{
	if (bind(port))
		if (_listen(qlen))
			return true;
	return false;
}

/**
 * Accept for incoming connections. If nonblk is true and there's no pending
 * requests on the socket, it returns NULL immediately. Otherwise, it blocks to
 * wait until a request is pended.
 *
 * \return
 * A pointer to TCPSocket representing incoming connection if success, or NULL
 * if failure. Note that the TCPSocket returned is managed by TCPServer and
 * should not be delete/free manually. TCPServer handles this.
 */
TCPSocket* TCPServer::accept(bool nonblk)
{
	if (setNonblock(nonblk)) {
		struct sockaddr_in inaddr;
		unsigned addlen = sizeof(inaddr);
		int sock;

		if ((sock = ::accept(_sockfd, (struct sockaddr *)&inaddr,
				&addlen)) < 0) {
			if (!(nonblk && (errno == EAGAIN || errno == EWOULDBLOCK)))
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
