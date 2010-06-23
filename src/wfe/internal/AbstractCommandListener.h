/**
 * \file AbstractCommandListener.h
 * \date Jun 14, 2010
 * \author samael
 */

#ifndef ABSTRACTCOMMANDLISTENER_H_
#define ABSTRACTCOMMANDLISTENER_H_

#include "TCPSocket.h"
#include "IRunnable.h"
#include "TLVCommand.h"
#include "Mutex.h"

namespace wfe
{

/**
 * Used to listen incoming commands.
 */
class AbstractCommandListener: public cml::IRunnable
{
public:
	AbstractCommandListener(cml::TCPSocket *sock):
		_done(false), _sock(sock), _mx() {}
	AbstractCommandListener(const AbstractCommandListener &o):
		cml::IRunnable(), _done(o._done), _sock(o._sock), _mx() {}
	virtual ~AbstractCommandListener() {}
	AbstractCommandListener& operator=(const AbstractCommandListener &o)
		{ _done = o._done; _sock = o._sock; return *this; }
	inline bool isDone()
		{ _mx.lock(); bool d = _done; _mx.unlock(); return d; }
	inline void setDone(bool d = true)
		{ _mx.lock(); _done = d; _mx.unlock(); }
	inline cml::TCPSocket* sock() const { return _sock; }
	void run();
	virtual void process(TLVCommand *cmd) = 0;
private:
	bool _done;
	cml::TCPSocket *_sock;
	cml::Mutex _mx;
};

}

#endif /* ABSTRACTCOMMANDLISTENER_H_ */
