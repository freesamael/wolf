/**
 * \file CQueuedTcpSocket.h
 * \date Jul 13, 2010
 * \author samael
 */

#ifndef CQUEUEDTCPSOCKET_H_
#define CQUEUEDTCPSOCKET_H_

#include <deque>
#include "CTcpSocket.h"
#include "CMutex.h"
#include "CWaitCondition.h"

namespace wolf
{

/**
 * A TCP socket implementation with reading queue.
 *
 * \note Buggy, dont use.
 */
class CQueuedTcpSocket: public CTcpSocket
{
public:
	CQueuedTcpSocket() throw(XSocket, XThread): _mx(), _cond(), _q()
			{ setBlockable(false); }
	CQueuedTcpSocket(int sock) throw(XSocket, XThread): CTcpSocket(sock), _mx(),
			_cond(), _q() {}
	~CQueuedTcpSocket() throw() {}
	ssize_t read(char *buf, size_t size) throw(XSocket);
	ssize_t write(const char *buf, size_t size) throw(XSocket);
	void readSocket() throw(XSocket);
	void close() throw(XSocket);

private:
	CMutex _mx;
	CWaitCondition _cond;
	std::deque<char> _q;
};

}

#endif /* CQUEUEDTCPSOCKET_H_ */
