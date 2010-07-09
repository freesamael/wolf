/**
 * \file CRunnerSideCommandSender.h
 * \date Jun 11, 2010
 * \author samael
 */

#ifndef CRUNNERSIDECOMMANDSENDER_H_
#define CRUNNERSIDECOMMANDSENDER_H_

#include <stdint.h>
#include "CTcpSocket.h"
#include "AWorkerActor.h"

namespace wfe
{

class CRunnerSideCommandSender
{
public:
	/// Join D2MCE computing group.
	void joinD2MCE(cml::CTcpSocket *sock, const std::string &appname);
	/// Say hello.
	void hello(cml::CTcpSocket *sock);
	/// Notify that a worker is finished.
	void workerFinished(cml::CTcpSocket *sock, uint32_t wseq,
			AWorkerActor *worker);
	/// Ask for stealing n workers.
	void stealWorker(cml::CTcpSocket *sock, uint16_t n);
	/// Ack that no worker to steal.
	void stealFailed(cml::CTcpSocket *sock);
	/// Send a worker out.
	void runWorker(cml::CTcpSocket *sock, uint32_t wseq,
			AWorkerActor *worker);
};

}

#endif /* CRUNNERSIDECOMMANDSENDER_H_ */
