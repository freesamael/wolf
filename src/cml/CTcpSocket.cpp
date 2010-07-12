/**
 * \file CTcpSocket.cpp
 * \date Mar 8, 2010
 * \author samael
 */

#include "CTcpSocket.h"

namespace cml
{

CTcpSocket::~CTcpSocket() throw()
{
	if (_autoclean) {
		for (unsigned i = 0; i < _ssocks.size(); i++)
			delete _ssocks[i];
	}
}

/**
 * Accept an incoming connection. The return slave socket is owned by this
 * master socket, and master socket will delete/free the slave sockets on
 * destruction.
 *
 * \return
 * Accepted socket. Or NULL if the socket is set as non-blocking and no padding
 * connection is found.
 */
CTcpSocket* CTcpSocket::accept() throw(XSocket)
{
	CTcpSocket *ssock = _state->accept(this);
	if (ssock)
		_ssocks.push_back(ssock);
	return ssock;
}

}
