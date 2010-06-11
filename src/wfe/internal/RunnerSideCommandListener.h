/**
 * \file RunnerSideCommandListener.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef RUNNERSIDECOMMANDLISTENER_H_
#define RUNNERSIDECOMMANDLISTENER_H_

#include "TCPSocket.h"
#include "IRunnable.h"
#include "Runner.h"
#include "TLVCommand.h"
#include "AbstractWorkerActor.h"

namespace wfe
{

/**
 * Used by runner to process commands from master.
 */
class RunnerSideCommandListener: public cml::IRunnable
{
public:
	RunnerSideCommandListener(Runner *parent, cml::TCPSocket *sock):
		_done(false), _parent(parent), _sock(sock) {}
	RunnerSideCommandListener(const RunnerSideCommandListener &o): _done(o._done),
			_parent(o._parent), _sock(o._sock) {}
	RunnerSideCommandListener& operator=(const RunnerSideCommandListener &o)
		{ _done = o._done; _parent = o._parent; _sock = o._sock; return *this; }
	void run();
	void setDone() { _done = true; }

private:
	void processCommand(TLVCommand *cmd);
	bool _done;
	Runner *_parent;
	cml::TCPSocket *_sock;
};

}

#endif /* RUNNERSIDECOMMANDLISTENER_H_ */
