/**
 * \file CommandListener.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef COMMANDLISTENER_H_
#define COMMANDLISTENER_H_

#include <TCPSocket.h>
#include <IRunnable.h>
#include "Runner.h"
#include "TLVMessage.h"
#include "AbstractWorkerActor.h"

namespace wfe
{

/**
 * Used by runner to process commands from master.
 */
class CommandListener: public cml::IRunnable
{
public:
	CommandListener(Runner *parent, cml::TCPSocket *sock):
		_done(false), _parent(parent), _sock(sock) {}
	CommandListener(const CommandListener &o): _done(o._done),
			_parent(o._parent), _sock(o._sock) {}
	CommandListener& operator=(const CommandListener &o)
		{ _done = o._done; _parent = o._parent; _sock = o._sock; return *this; }
	void run();
	void setDone() { _done = true; }

private:
	void processCommand(TLVMessage *cmd);
	bool _done;
	Runner *_parent;
	cml::TCPSocket *_sock;
};

}

#endif /* COMMANDLISTENER_H_ */
