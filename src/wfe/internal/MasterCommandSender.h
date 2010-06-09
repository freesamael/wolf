/**
 * \file MasterCommandSender.h
 * \date May 27, 2010
 * \author samael
 */

#ifndef MASTERCOMMANDSENDER_H_
#define MASTERCOMMANDSENDER_H_

#include <vector>
#include <string>
#include <stdint.h>
#include "TCPSocket.h"
#include "AbstractWorkerActor.h"

namespace wfe
{

/**
 * Internal class used by Master to send command.
 */
class MasterCommandSender
{
public:
	/// Join D2MCE computing group.
	void joinD2MCE(const std::string &appname);
	/// Send hello message.
	void hello(uint16_t rport);
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

#endif /* MASTERCOMMANDSENDER_H_ */
