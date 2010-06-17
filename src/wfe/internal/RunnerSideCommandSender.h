/**
 * \file RunnerSideCommandSender.h
 * \date Jun 11, 2010
 * \author samael
 */

#ifndef RUNNERSIDECOMMANDSENDER_H_
#define RUNNERSIDECOMMANDSENDER_H_

#include <stdint.h>
#include "TCPSocket.h"
#include "AbstractWorkerActor.h"

namespace wfe
{

class RunnerSideCommandSender
{
public:
	/// Join D2MCE computing group.
	void joinD2MCE(cml::TCPSocket *sock, const std::string &appname);
	/// Say hello.
	void hello(cml::TCPSocket *sock);
	/// Notify that a worker is finished.
	void workerFinished(cml::TCPSocket *sock, uint32_t wseq,
			AbstractWorkerActor *worker);
	/// Ask for stealing a worker.
	void stealWorker(cml::TCPSocket *sock);
	/// Send a worker out.
	void runWorker(cml::TCPSocket *sock, uint32_t wseq,
			AbstractWorkerActor *worker);
};

}

#endif /* RUNNERSIDECOMMANDSENDER_H_ */
