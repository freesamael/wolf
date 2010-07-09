/**
 * \file CRunnerSideCommandListener.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "CTlvUint32.h"
#include "CTlvUint16.h"
#include "CTlvReaderWriter.h"
#include "HelperMacros.h"
#include "CRunnerSideCommandListener.h"
#include "AWorkerActor.h"

using namespace cml;

namespace wfe
{

void CRunnerSideCommandListener::process(CTlvCommand *cmd)
{
	// Command RUNNER_ADD
	if (cmd->command() == CTlvCommand::RUNNER_ADD) {
		PINF_2("Got command RUNNER_ADD.");
		for (unsigned i = 0; i < cmd->parameters().size(); i++) {
			CTlvUint32 *u32;
			if ((u32 = dynamic_cast<CTlvUint32 *>(cmd->parameters()[i]))) {
				CHostAddress addr((in_addr_t)u32->value());
				_runner->connectRunner(addr);
				delete u32;
			} else {
				PERR("Invalid parameter.");
			}
		}

	// Command RUNNER_START
	} else if (cmd->command() == CTlvCommand::RUNNER_START) {
		PINF_2("Got command RUNNER_START.");
		_runner->startWorking();

	// Command WORKER_RUN
	} else if (cmd->command() == CTlvCommand::WORKER_RUN) {
		PINF_2("Got command WORKER_RUN.");
		if (cmd->parameters().size() != 2) { // [wseq, worker]
			PERR("Invalid parameters.");
			cmd->setAutoclean(true);
		} else {
			CTlvUint32 *u32;
			AWorkerActor *worker;
			if (!(u32 = dynamic_cast<CTlvUint32 *>(cmd->parameters()[0]))) {
				PERR("Invalid parameters.");
				cmd->setAutoclean(true);
			} else if (!(worker =
					dynamic_cast<AWorkerActor *>(cmd->parameters()[1]))) {
				PERR("Invalid parameters.");
				cmd->setAutoclean(true);
			} else {
				_runner->putWorker(u32->value(), worker, sock());
				delete u32;
			}
		}

	// Command WORKER_STEAL
	} else if (cmd->command() == CTlvCommand::WORKER_STEAL) {
		PINF_2("Got command WORKER_STEAL.");
		if (cmd->parameters().size() != 1) { // number of workers to steal
			PERR("Invalid parameters.");
			cmd->setAutoclean(true);
		} else {
			CTlvUint16 *u16;
			if (!(u16 = dynamic_cast<CTlvUint16 *>(cmd->parameters()[0]))) {
				PERR("Invalid parameters.");
				cmd->setAutoclean(true);
			} else {
				_runner->sendWorker(sock(), u16->value());
			}
		}

	// Command WORKER_STEAL_FAILED
	} else if (cmd->command() == CTlvCommand::WORKER_STEAL_FAILED) {
		_runner->workerStealFailed(sock());

	// Command SHUTDOWN
	} else if (cmd->command() == CTlvCommand::SHUTDOWN) {
		PINF_2("Got command SHUTDOWN.");
		_runner->shutdown();

	// Unexpected commands
	} else {
		PERR("Unexpected command \"" <<
				CTlvCommand::CommandString[cmd->command()] << "\".");
	}
}

}
