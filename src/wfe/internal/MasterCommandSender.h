/**
 * \file MasterCommandSender.h
 * \date May 27, 2010
 * \author samael
 */

#ifndef MASTERCOMMANDSENDER_H_
#define MASTERCOMMANDSENDER_H_

#include <stdint.h>
#include <TCPSocket.h>
#include "AbstractWorkerActor.h"

namespace wfe
{

class MasterCommandSender
{
public:
	/// Send hello message.
	void hello(uint16_t runner_port);
	/// Shutdown the runner.
	void shutdown(cml::TCPSocket *runner);
	/// Send an actor to run.
	void runActor(cml::TCPSocket *runner, AbstractWorkerActor *actor);
};

}

#endif /* MASTERCOMMANDSENDER_H_ */
