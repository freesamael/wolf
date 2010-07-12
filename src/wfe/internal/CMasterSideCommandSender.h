/**
 * \file CMasterSideCommandSender.h
 * \date May 27, 2010
 * \author samael
 */

#ifndef CMASTERSIDECOMMANDSENDER_H_
#define CMASTERSIDECOMMANDSENDER_H_

#include <vector>
#include <string>
#include <stdint.h>
#include "CTcpSocket.h"
#include "AWorkerActor.h"
#include "CMaster.h"
#include "HelperMacros.h"

namespace wfe
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
	void hello(uint16_t rport, const cml::CHostAddress &addr);
	/// Ask a runner to add other runners.
	void addRunner(cml::CTcpSocket *rsock, const std::vector<cml::CHostAddress> &addrs);
	/// Tell a runner to start working.
	void startRunner(cml::CTcpSocket *rsock);
	/// Shutdown the runner.
	void shutdown(cml::CTcpSocket *rsock);
	/// Send an actor to run.
	/// \return sequence number of the worker.
	uint32_t runWorker(cml::CTcpSocket *rsock, AWorkerActor *worker);

private:
	static uint32_t _wseq; ///< Worker sequence number.
};

}

#endif /* CMASTERSIDECOMMANDSENDER_H_ */
