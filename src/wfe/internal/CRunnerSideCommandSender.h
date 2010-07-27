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

namespace wolf
{

class CRunnerSideCommandSender
{
public:
	/// Join D2MCE computing group.
	void joinD2MCE(wolf::CTcpSocket *sock, const std::string &appname);
	/// Say hello.
	void hello(wolf::CTcpSocket *sock);
	/// Notify that a worker is finished.
	void workerFinished(wolf::CTcpSocket *sock, uint32_t wseq,
			AWorkerActor *worker);
	/// Ask for stealing n workers.
	void stealWorker(wolf::CTcpSocket *sock, uint16_t n);
	/// Ack that no worker to steal.
	void stealFailed(wolf::CTcpSocket *sock);
	/// Send a worker out.
	void runWorker(wolf::CTcpSocket *sock, uint32_t wseq,
			AWorkerActor *worker);
};

}

#endif /* CRUNNERSIDECOMMANDSENDER_H_ */
