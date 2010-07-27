/**
 * \file CRunnerSideCommandListener.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef CRUNNERSIDECOMMANDLISTENER_H_
#define CRUNNERSIDECOMMANDLISTENER_H_

#include "ACommandListener.h"
#include "CRunner.h"

namespace wolf
{

/**
 * Runner side commands listener.
 */
class CRunnerSideCommandListener: public ACommandListener
{
public:
	CRunnerSideCommandListener(CRunner *runner, CTcpSocket *sock):
		ACommandListener(sock), _runner(runner) {}
	CRunnerSideCommandListener(const CRunnerSideCommandListener &o):
		ACommandListener(o), _runner(o._runner) {}
	CRunnerSideCommandListener& operator=(const CRunnerSideCommandListener &o)
		{ ACommandListener::operator=(o); _runner = o._runner;
		return *this; }
	void process(CTlvCommand *cmd);

private:
	CRunner *_runner;
};

}

#endif /* CRUNNERSIDECOMMANDLISTENER_H_ */
