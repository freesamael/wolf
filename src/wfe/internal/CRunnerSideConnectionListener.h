/**
 * \file CRunnerSideConnectionListener.h
 * \date Jun 11, 2010
 * \author samael
 */

#ifndef CRUNNERSIDECONNECTIONLISTENER_H_
#define CRUNNERSIDECONNECTIONLISTENER_H_

#include "AConnectionListener.h"
#include "CRunner.h"

namespace wfe
{

/**
 * Runner side runner connections listener.
 */
class CRunnerSideConnectionListener: public AConnectionListener
{
public:
	CRunnerSideConnectionListener(CRunner *runner, cml::CTcpSocket *lsock,
			uint16_t lport): AConnectionListener(lsock, lport),
			_runner(runner) {}
	void notify(cml::CTcpSocket *sock);

private:
	CRunnerSideConnectionListener(const CRunnerSideConnectionListener &UNUSED(o)):
		AConnectionListener(NULL, 0), _runner(NULL) {}
	CRunnerSideConnectionListener& operator=(const CRunnerSideConnectionListener
			&UNUSED(o)) { return *this; }
	CRunner *_runner;
};

}

#endif /* CRUNNERSIDECONNECTIONLISTENER_H_ */
