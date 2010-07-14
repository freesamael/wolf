/**
 * \file CTcpServer.cpp
 * \date Jul 13, 2010
 * \author samael
 */

#include "CTcpServer.h"
#include "CQueuedTcpSocket.h"
#include "internal/CConnectedSocketState.h"

namespace cml
{

CTcpServer::~CTcpServer() throw()
{
	if (_ac) {
		for (unsigned i = 0; i < _ssocks.size(); i++)
			delete _ssocks[i];
	}
}

/**
 * Accept an incoming connection. The return slave socket is owned by this
 * master socket, and master socket will destroy the slave sockets on
 * destruction unless autoclean is set to false.
 *
 * \param[in] type
 * DIRECT for CTcpSocket, QUEUED for CTcpQueuedSocket.
 *
 * \return
 * Accepted socket or NULL if the socket is non-blocking and no padding
 * connection has been found.
 */
CTcpSocket* CTcpServer::accept(SlaveType type) throw(XSocket)
{
	int sockfd = state()->accept(this);
	if (sockfd == -1)
		return NULL;

	CTcpSocket *ssock;
	if (type == QUEUED)
		ssock = new CQueuedTcpSocket(sockfd);
	else
		ssock = new CTcpSocket(sockfd);
	ssock->changeState(CConnectedSocketState::instance());

	_ssocks.push_back(ssock);
	return ssock;
}

}
