/**
 * \file ACommandListener.h
 * \date Jun 14, 2010
 * \author samael
 */

#ifndef ACOMMANDLISTENER_H_
#define ACOMMANDLISTENER_H_

#include "CThread.h"
#include "CTcpSocket.h"
#include "CTlvCommand.h"
#include "CMutex.h"

namespace wolf
{

/**
 * Used to listen incoming commands.
 */
class ACommandListener: public wolf::CThread
{
public:
	ACommandListener(wolf::CTcpSocket *sock):
		_done(false), _sock(sock), _mx() {}
	ACommandListener(const ACommandListener &o):
		wolf::CThread(), _done(o._done), _sock(o._sock), _mx() {}
	virtual ~ACommandListener() {}
	ACommandListener& operator=(const ACommandListener &o)
		{ _done = o._done; _sock = o._sock; return *this; }
	inline bool isDone()
		{ _mx.lock(); bool d = _done; _mx.unlock(); return d; }
	inline void setDone(bool d = true)
		{ _mx.lock(); _done = d; _mx.unlock(); }
	inline wolf::CTcpSocket* sock() const { return _sock; }
	void run();
	virtual void process(CTlvCommand *cmd) = 0;
private:
	bool _done;
	wolf::CTcpSocket *_sock;
	wolf::CMutex _mx;
};

}

#endif /* ACOMMANDLISTENER_H_ */
