/**
 * \file CQueuedTcpDataReader.h
 * \date Jul 12, 2010
 * \author samael
 */

#ifndef CQUEUEDTCPDATAREADER_H_
#define CQUEUEDTCPDATAREADER_H_

#include <map>
#include "IRunnable.h"
#include "CMutex.h"
#include "CQueuedTcpSocket.h"

namespace wolf
{

/**
 * A reader designed for CTcpQueuedSocket.
 */
class CQueuedTcpDataReader: public IRunnable
{
public:
	CQueuedTcpDataReader();
	~CQueuedTcpDataReader();
	void addSocket(CQueuedTcpSocket *sock);
	void removeSocket(CQueuedTcpSocket *sock);
	inline void setDone(bool d = true) { _mx.lock(); _done = d; _mx.unlock(); }
	inline bool isDone() { _mx.lock(); bool d = _done; _mx.unlock(); return d; }
	void run();

private:
	bool _done;
	CMutex _mx;
	std::map<int, CQueuedTcpSocket *> _socks;
};

}

#endif /* CQUEUEDTCPDATAREADER_H_ */
