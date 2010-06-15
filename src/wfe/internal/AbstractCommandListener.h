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

namespace wfe
{

/**
 * Used to listen incoming commands.
 */
class AbstractCommandListener: public cml::IRunnable
{
public:
	AbstractCommandListener(cml::TCPSocket *sock): _done(false), _sock(sock) {}
	AbstractCommandListener(const AbstractCommandListener &o):
		_done(false), _sock(o._sock) {}
	virtual ~AbstractCommandListener() {}
	AbstractCommandListener& operator=(const AbstractCommandListener &o)
		{ _sock = o._sock; return *this; }
	inline void setDone() { _done = true; }
	void run();
	virtual void process(TLVCommand *cmd) = 0;
private:
	bool _done;
	cml::TCPSocket *_sock;
};

}

#endif /* ABSTRACTCOMMANDLISTENER_H_ */
