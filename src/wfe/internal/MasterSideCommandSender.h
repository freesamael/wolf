/**
 * \file MasterSideCommandSender.h
 * \date May 27, 2010
 * \author samael
 */

#ifndef MASTERSIDECOMMANDSENDER_H_
#define MASTERSIDECOMMANDSENDER_H_

#include <vector>
#include <string>
#include <stdint.h>
#include "TCPSocket.h"
#include "AbstractWorkerActor.h"
#include "Master.h"
#include "HelperMacros.h"

namespace wfe
{

/**
 * Internal class used by Master to send command.
 */
class MasterSideCommandSender
{
public:
	/// Join D2MCE computing group.
	void joinD2MCE(const std::string &appname);
	/// Send hello message.
	void hello(uint16_t rport, const cml::HostAddress &addr =
			cml::HostAddress::BroadcastAddress, int ttl = 1);
	/// Ask a runner to add other runners.
	void addRunner(cml::TCPSocket *rsock, const std::vector<cml::HostAddress> &addrs);
	/// Tell a runner to start working.
	void startRunner(cml::TCPSocket *rsock);
	/// Shutdown the runner.
	void shutdown(cml::TCPSocket *rsock);
	/// Send an actor to run.
	/// \return sequence number of the worker.
	uint32_t runWorker(cml::TCPSocket *rsock, AbstractWorkerActor *worker);

private:
	static uint32_t _wseq; ///< Worker sequence number.
};

}

#endif /* MASTERSIDECOMMANDSENDER_H_ */
