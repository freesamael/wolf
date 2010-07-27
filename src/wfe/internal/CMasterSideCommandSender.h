/**
 * \file CMasterSideCommandSender.h
 * \date May 27, 2010
 * \author samael
 */

#ifndef CMASTERSIDECOMMANDSENDER_H_
#define CMASTERSIDECOMMANDSENDER_H_

#include <vector>
#include <string>
#include <inttypes.h>
#include "CTcpSocket.h"
#include "AWorkerActor.h"
#include "CMaster.h"
#include "HelperMacros.h"

namespace wolf
{

/**
 * Internal class used by Master to send command.
 */
class CMasterSideCommandSender
{
public:
	/// Join D2MCE computing group.
	void joinD2MCE(const std::string &appname);
	/// Send hello message.
	void hello(in_port_t rport, const wolf::CHostAddress &addr);
	/// Ask a runner to add other runners.
	void addRunner(wolf::CTcpSocket *rsock, const std::vector<wolf::CHostAddress> &addrs);
	/// Tell a runner to start working.
	void startRunner(wolf::CTcpSocket *rsock);
	/// Shutdown the runner.
	void shutdown(wolf::CTcpSocket *rsock);
	/// Send an actor to run.
	/// \return sequence number of the worker.
	uint32_t runWorker(wolf::CTcpSocket *rsock, AWorkerActor *worker);

private:
	static uint32_t _wseq; ///< Worker sequence number.
};

}

#endif /* CMASTERSIDECOMMANDSENDER_H_ */
