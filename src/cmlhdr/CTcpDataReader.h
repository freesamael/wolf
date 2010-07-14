/**
 * \file CTcpDataReader.h
 * \date Jul 12, 2010
 * \author samael
 */

#ifndef CTCPDATAREADER_H_
#define CTCPDATAREADER_H_

#include <map>
#include "IRunnable.h"
#include "CMutex.h"
#include "CTcpQueuedSocket.h"

namespace cml
{

/**
 * A reader designed for CTcpQueuedSocket.
 */
class CTcpDataReader: public IRunnable
{
public:
	CTcpDataReader();
	~CTcpDataReader();
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

#endif /* CTCPDATAREADER_H_ */
