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

namespace wfe
{

/**
 * Used to listen incoming commands.
 */
class ACommandListener: public cml::CThread
{
public:
	ACommandListener(cml::CTcpSocket *sock):
		_done(false), _sock(sock), _mx() {}
	ACommandListener(const ACommandListener &o):
		cml::CThread(), _done(o._done), _sock(o._sock), _mx() {}
	virtual ~ACommandListener() {}
	ACommandListener& operator=(const ACommandListener &o)
		{ _done = o._done; _sock = o._sock; return *this; }
	inline bool isDone()
		{ _mx.lock(); bool d = _done; _mx.unlock(); return d; }
	inline void setDone(bool d = true)
		{ _mx.lock(); _done = d; _mx.unlock(); }
	inline cml::CTcpSocket* sock() const { return _sock; }
	void run();
	virtual void process(CTlvCommand *cmd) = 0;
private:
	bool _done;
	cml::CTcpSocket *_sock;
	cml::CMutex _mx;
};

}

#endif /* ACOMMANDLISTENER_H_ */
