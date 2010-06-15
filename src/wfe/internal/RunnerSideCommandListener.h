/**
 * \file RunnerSideCommandListener.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef RUNNERSIDECOMMANDLISTENER_H_
#define RUNNERSIDECOMMANDLISTENER_H_

#include "AbstractCommandListener.h"
#include "Runner.h"

namespace wfe
{

/**
 * Runner side commands listener.
 */
class RunnerSideCommandListener: public AbstractCommandListener
{
public:
	RunnerSideCommandListener(Runner *runner, cml::TCPSocket *sock):
		AbstractCommandListener(sock), _runner(runner) {}
	RunnerSideCommandListener(const RunnerSideCommandListener &o):
		AbstractCommandListener(o), _runner(o._runner) {}
	RunnerSideCommandListener& operator=(const RunnerSideCommandListener &o)
		{ AbstractCommandListener::operator=(o); _runner = o._runner;
		return *this; }
	void process(TLVCommand *cmd);

private:
	Runner *_runner;
};

}

#endif /* RUNNERSIDECOMMANDLISTENER_H_ */
