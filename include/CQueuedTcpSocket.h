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
	CQueuedTcpSocket() : _mx(), _cond(), _q()
			{ setBlockable(false); }
	CQueuedTcpSocket(int sock) : CTcpSocket(sock), _mx(),
			_cond(), _q() {}
	~CQueuedTcpSocket()  {}
	ssize_t read(char *buf, size_t size);
	ssize_t write(const char *buf, size_t size);
	void readSocket();
	void close();

private:
	CMutex _mx;
	CWaitCondition _cond;
	std::deque<char> _q;
};

}

#endif /* CQUEUEDTCPSOCKET_H_ */
