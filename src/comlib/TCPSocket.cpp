/*
 * TCPSocket.cpp
 *
 *  Created on: Mar 8, 2010
 *      Author: samael
 */

#include <cstdio>
#include <errno.h>
#include "TCPSocket.h"

namespace cml
{

TCPSocket::~TCPSocket()
{
	for (int i = 0; i < (int)_ssocks.size(); i++)
		delete _ssocks[i];
}

/**
 * Accept an incoming connection. The return slave socket is owned by this
 * master socket, and master socket will delete/free the slave sockets on
 * destruction.
 *
 * \return
 * Accepted socket. Or NULL for error or no padding connection if the socket is
 * set as non-blocking.
 */
TCPSocket* TCPSocket::accept()
{
	TCPSocket *ssock = _state->accept(this);
	if (ssock)
		_ssocks.push_back(ssock);
	return ssock;
}

}
