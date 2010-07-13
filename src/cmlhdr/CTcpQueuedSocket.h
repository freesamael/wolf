/**
 * \file CTcpQueuedSocket.h
 * \date Jul 13, 2010
 * \author samael
 */

#ifndef CTCPQUEUEDSOCKET_H_
#define CTCPQUEUEDSOCKET_H_

#include <deque>
#include "CTcpSocket.h"
#include "CMutex.h"
#include "CWaitCondition.h"

namespace cml
{

class CTcpQueuedSocket: public CTcpSocket
{
public:
	CTcpQueuedSocket() throw(XSocket, XThread): _mx(), _cond(), _q() {}
	CTcpQueuedSocket(int sock) throw(XSocket, XThread): CTcpSocket(sock), _mx(),
			_cond(), _q() {}
	~CTcpQueuedSocket() throw() {}
	ssize_t read(char *buf, size_t size) throw(XSocket);
	void readSocket() throw(XSocket);
	void close() throw(XSocket);

private:
	CMutex _mx;
	CWaitCondition _cond;
	std::deque<char> _q;
};

}

#endif /* CTCPQUEUEDSOCKET_H_ */
