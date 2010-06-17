/**
 * \file RunnerSideCommandListener.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include <iostream>
#include "TLVUInt32.h"
#include "TLVReaderWriter.h"
#include "HelperMacros.h"
#include "RunnerSideCommandListener.h"
#include "AbstractWorkerActor.h"

using namespace cml;

namespace wfe
{

void RunnerSideCommandListener::process(TLVCommand *cmd)
{
	PINF_2("Got a command, identifying...");
	if (cmd->command() == TLVCommand::RUNNER_ADD) {
		PINF_2("Processing RUNNER_ADD command.");
		for (unsigned i = 0; i < cmd->parameters().size(); i++) {
			TLVUInt32 *u32;
			if ((u32 = dynamic_cast<TLVUInt32 *>(cmd->parameters()[i]))) {
				HostAddress addr((in_addr_t)u32->value());
				_runner->connectRunner(addr);
				delete u32;
			} else {
				PERR("Invalid parameter.");
			}
		}
	} else if (cmd->command() == TLVCommand::RUNNER_START) {
		PINF_2("Processing RUNNER_START command.");
		_runner->startWorking();
	} else if (cmd->command() == TLVCommand::WORKER_RUN) {
		PINF_2("Processing WORKER_RUN command.");
		/// TODO: complete worker_run processing code.
	} else if (cmd->command() == TLVCommand::WORKER_STEAL) {
		PINF_2("Processing WORKER_STEAL command.");
		_runner->sendWorker(sock());
	} else if (cmd->command() == TLVCommand::SHUTDOWN) {
		PINF_2("Processing SHUTDOWN command.");
		_runner->shutdown();
	} else {
		PERR("Unexpected command \"" <<
				TLVCommand::CommandString[cmd->command()] << "\".");
	}
}

}
