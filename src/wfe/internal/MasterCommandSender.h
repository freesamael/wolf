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

class MasterCommandSender
{
public:
	/// Join D2MCE computing group.
	void joinD2MCE(const std::string &appname);
	/// Send hello message.
	void hello(uint16_t runner_port);
	/// Tell a runner to start working.
	void start(cml::TCPSocket *runner);
	/// Shutdown the runner.
	void shutdown(cml::TCPSocket *runner);
	/// Send an actor to run.
	void runActor(cml::TCPSocket *runner, AbstractWorkerActor *actor);
	/// Ask a runner to add other runners.
	void addRunner(cml::TCPSocket *runner, std::vector<cml::HostAddress> addrs);
};

}

#endif /* MASTERCOMMANDSENDER_H_ */
