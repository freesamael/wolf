/**
 * \file CRunnerSideCommandListener.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include "CRunnerSideCommandListener.h"

#include <iostream>
#include <sstream>
#include "CTlvUint32.h"
#include "CTlvUint16.h"
#include "HelperMacros.h"
#include "AWorkerActor.h"
#include "XTlvCommand.h"

namespace wolf
{

void CRunnerSideCommandListener::process(CTlvCommand *cmd)
{
	// Command RUNNER_ADD
	if (cmd->command() == CTlvCommand::RUNNER_ADD) {
		for (unsigned i = 0; i < cmd->parameters().size(); i++) {
			CTlvUint32 *u32;
			if ((u32 = dynamic_cast<CTlvUint32 *>(cmd->parameters()[i]))) {
				CHostAddress addr((in_addr_t)u32->value());
				_runner->connectRunner(addr);
				delete u32;
			} else {
				throw XTlvCommand(XTlvCommand::INVALID_PARAM, *cmd);
			}
		}

	// Command RUNNER_START
	} else if (cmd->command() == CTlvCommand::RUNNER_START) {
		_runner->startWorking();

	// Command WORKER_RUN
	} else if (cmd->command() == CTlvCommand::WORKER_RUN) {
		CTlvUint32 *u32;
		AWorkerActor *worker;

		// Check #parameters.
		if (cmd->parameters().size() != 2) { // [wseq, worker]
			cmd->setAutoclean(true);
			throw XTlvCommand(XTlvCommand::INVALID_PARAM_NUM, *cmd);
		}

		// Check p1.
		if (!(u32 = dynamic_cast<CTlvUint32 *>(cmd->parameters()[0]))) {
			cmd->setAutoclean(true);
			throw XTlvCommand(XTlvCommand::INVALID_PARAM, *cmd);
		}

		// Check p2.
		if (!(worker =
				dynamic_cast<AWorkerActor *>(cmd->parameters()[1]))) {
			cmd->setAutoclean(true);
			throw XTlvCommand(XTlvCommand::INVALID_PARAM, *cmd);
		}

		_runner->putWorker(u32->value(), worker, sock());
		delete u32;

	// Command WORKER_STEAL
	} else if (cmd->command() == CTlvCommand::WORKER_STEAL) {
		CTlvUint32 *u32;

		// Check #parameters.
		if (cmd->parameters().size() != 1) { // number of workers to steal
			cmd->setAutoclean(true);
			throw XTlvCommand(XTlvCommand::INVALID_PARAM_NUM, *cmd);
		}

		// Check p1.
		if (!(u32 = dynamic_cast<CTlvUint32 *>(cmd->parameters()[0]))) {
			cmd->setAutoclean(true);
			throw XTlvCommand(XTlvCommand::INVALID_PARAM, *cmd);
		}

		_runner->sendWorker(sock(), u32->value());

	// Command WORKER_STEAL_FAILED
	} else if (cmd->command() == CTlvCommand::WORKER_STEAL_FAILED) {
		_runner->workerStealFailed(sock());

	// Command SHUTDOWN
	} else if (cmd->command() == CTlvCommand::SHUTDOWN) {
		_runner->shutdown();

	// Unexpected commands
	} else {
		throw XTlvCommand(XTlvCommand::UNEXPECTED_COMMAND, *cmd);
	}
}

}
