/**
 * \file RunnerSideCommandListener.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include <iostream>
#include "TLVReaderWriter.h"
#include "HelperMacros.h"
#include "RunnerSideCommandListener.h"
#include "AbstractWorkerActor.h"

using namespace cml;

namespace wfe
{

void RunnerSideCommandListener::process(TLVCommand *cmd)
{
	PINF_2("Processing a command.");
//	if (cmd->command() == TLVCommand::WORKER_RUN) {
//		// Test parameter.
//		AbstractWorkerActor *actor;
//		if (!(actor = dynamic_cast<AbstractWorkerActor *>(cmd->parameter()))) {
//			PERR("Invalid parameter.");
//		}
		// Add to waiting queue.
//		_parent->enqueue(actor);
//	} else if (cmd->command() == TLVCommand::SHUTDOWN) {
//		PINF_2("Ending runner.");
//		_done = true;
//	} else {
//		PERR("Unexpected command \"" <<
//				TLVCommand::CommandString[cmd->command()] << "\".");
//	}
}

}
