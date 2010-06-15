/**
 * \file RunnerSideConnectionListener.h
 * \date Jun 11, 2010
 * \author samael
 */

#ifndef RUNNERSIDECONNECTIONLISTENER_H_
#define RUNNERSIDECONNECTIONLISTENER_H_

#include "AbstractConnectionListener.h"
#include "Runner.h"

namespace wfe
{

/**
 * Runner side runner connections listener.
 */
class RunnerSideConnectionListener: public AbstractConnectionListener
{
public:
	RunnerSideConnectionListener(Runner *runner, cml::TCPSocket *lsock,
			uint16_t lport): AbstractConnectionListener(lsock, lport),
			_runner(runner) {}
	void notify(cml::TCPSocket *sock);

private:
	RunnerSideConnectionListener(const RunnerSideConnectionListener &UNUSED(o)):
		AbstractConnectionListener(NULL, 0), _runner(NULL) {}
	RunnerSideConnectionListener& operator=(const RunnerSideConnectionListener
			&UNUSED(o)) { return *this; }
	Runner *_runner;
};

}

#endif /* RUNNERSIDECONNECTIONLISTENER_H_ */
