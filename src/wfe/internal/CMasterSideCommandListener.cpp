/**
 * \file CMasterSideCommandListener.cpp
 * \date Jun 3, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "CTlvUint32.h"
#include "CMasterSideCommandListener.h"

using namespace cml;

namespace wfe
{

void CMasterSideCommandListener::process(CTlvCommand *cmd)
{
	if (cmd->command() == CTlvCommand::WORKER_FINISHED) {
		PINF_2("Got command WORKER_FINISHED.");
		CTlvUint32 *u32;
		AWorkerActor *worker;
		if (cmd->parameters().size() != 2) { // [id, worker]
			PERR("Invalid number of parameters.");
			return;
		}
		if (!(u32 = dynamic_cast<CTlvUint32 *>(cmd->parameters()[0]))) {
			PERR("Invalid parameter.");
			return;
		}
		if (!(worker = dynamic_cast<AWorkerActor *>(cmd->parameters()[1]))) {
			PERR("Invalid parameter.");
			delete u32;
			return;
		}
		PINF_2("Worker " << u32->value() << " finished by runner " <<
				sock()->peerAddress().toString());
		_master->putFinishWorker(u32->value(), worker);
		delete u32;
	} else {
		PERR("Unexpected command \"" <<
				CTlvCommand::CommandString[cmd->command()] << "\".");
	}
}

}
