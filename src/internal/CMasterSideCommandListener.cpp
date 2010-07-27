/**
 * \file CMasterSideCommandListener.cpp
 * \date Jun 3, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "CTlvUint32.h"
#include "HelperMacros.h"
#include "CMasterSideCommandListener.h"
#include "XTlvCommand.h"

using namespace wolf;

namespace wolf
{

void CMasterSideCommandListener::process(CTlvCommand *cmd)
{
	if (cmd->command() == CTlvCommand::WORKER_FINISHED) {
		CTlvUint32 *u32;
		AWorkerActor *worker;

		// Check #parameters.
		if (cmd->parameters().size() != 2) { // [id, worker]
			cmd->setAutoclean(true);
			throw XTlvCommand(__PRETTY_FUNCTION__, __LINE__,
					XTlvCommand::INVALID_PARAM_NUM, *cmd);
		}

		// Check p1.
		if (!(u32 = dynamic_cast<CTlvUint32 *>(cmd->parameters()[0]))) {
			cmd->setAutoclean(true);
			throw XTlvCommand(__PRETTY_FUNCTION__, __LINE__,
					XTlvCommand::INVALID_PARAM, *cmd);
		}

		// Check p2.
		if (!(worker = dynamic_cast<AWorkerActor *>(cmd->parameters()[1]))) {
			cmd->setAutoclean(true);
			throw XTlvCommand(__PRETTY_FUNCTION__, __LINE__,
					XTlvCommand::INVALID_PARAM, *cmd);
		}

		PINF_2("Worker " << u32->value() << " finished by runner " <<
				sock()->peerAddress().toString());
		_master->putFinishWorker(u32->value(), worker);
		delete u32;
	} else {
		throw XTlvCommand(__PRETTY_FUNCTION__, __LINE__,
				XTlvCommand::UNEXPECTED_COMMAND, *cmd);
	}
}

}
