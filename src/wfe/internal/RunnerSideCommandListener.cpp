/**
 * \file RunnerSideCommandListener.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "TLVUInt32.h"
#include "TLVUInt16.h"
#include "TLVReaderWriter.h"
#include "HelperMacros.h"
#include "RunnerSideCommandListener.h"
#include "AbstractWorkerActor.h"

using namespace cml;

namespace wfe
{

void RunnerSideCommandListener::process(TLVCommand *cmd)
{
	// Command RUNNER_ADD
	if (cmd->command() == TLVCommand::RUNNER_ADD) {
		PINF_2("Got command RUNNER_ADD.");
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

	// Command RUNNER_START
	} else if (cmd->command() == TLVCommand::RUNNER_START) {
		PINF_2("Got command RUNNER_START.");
		_runner->startWorking();

	// Command WORKER_RUN
	} else if (cmd->command() == TLVCommand::WORKER_RUN) {
		PINF_2("Got command WORKER_RUN.");
		if (cmd->parameters().size() != 2) { // [wseq, worker]
			PERR("Invalid parameters.");
			cmd->setAutoclean(true);
		} else {
			TLVUInt32 *u32;
			AbstractWorkerActor *worker;
			if (!(u32 = dynamic_cast<TLVUInt32 *>(cmd->parameters()[0]))) {
				PERR("Invalid parameters.");
				cmd->setAutoclean(true);
			} else if (!(worker =
					dynamic_cast<AbstractWorkerActor *>(cmd->parameters()[1]))) {
				PERR("Invalid parameters.");
				cmd->setAutoclean(true);
			} else {
				_runner->putWorker(u32->value(), worker, sock());
				delete u32;
			}
		}

	// Command WORKER_STEAL
	} else if (cmd->command() == TLVCommand::WORKER_STEAL) {
		PINF_2("Got command WORKER_STEAL.");
		if (cmd->parameters().size() != 1) { // number of workers to steal
			PERR("Invalid parameters.");
			cmd->setAutoclean(true);
		} else {
			TLVUInt16 *u16;
			if (!(u16 = dynamic_cast<TLVUInt16 *>(cmd->parameters()[0]))) {
				PERR("Invalid parameters.");
				cmd->setAutoclean(true);
			} else {
				_runner->sendWorker(sock(), u16->value());
			}
		}

	// Command WORKER_STEAL_FAILED
	} else if (cmd->command() == TLVCommand::WORKER_STEAL_FAILED) {
		_runner->workerStealFailed(sock());

	// Command SHUTDOWN
	} else if (cmd->command() == TLVCommand::SHUTDOWN) {
		PINF_2("Got command SHUTDOWN.");
		_runner->shutdown();

	// Unexpected commands
	} else {
		PERR("Unexpected command \"" <<
				TLVCommand::CommandString[cmd->command()] << "\".");
	}
}

}
