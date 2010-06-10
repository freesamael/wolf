/**
 * \file CommandListener.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include <iostream>
#include "TLVReaderWriter.h"
#include "HelperMacros.h"
#include "CommandListener.h"
#include "AbstractWorkerActor.h"

using namespace cml;

namespace wfe
{

/**
 * Read command and execute.
 */
void CommandListener::run()
{
	TLVReaderWriter tcprw(_sock);
	ITLVObject *inobj;
	TLVCommand *inmsg = NULL;

	while (!_done) {
		if (!(inobj = tcprw.read()))
			break; // End of file.
		if (!(inmsg = dynamic_cast<TLVCommand *>(inobj))) {
			PERR("Invalid incoming message.");
			delete inobj;
		} else {
			processCommand(inmsg);
			delete inmsg;
		}
	}
	PINFO_2("Running loop ends.");
}

/**
 * Process command. Return true if the actor is successfully extracted and
 * executed.
 */
void CommandListener::processCommand(TLVCommand *cmd)
{
	PINFO_2("Processing a command.");
	if (cmd->command() == TLVCommand::WORKER_RUN) {
		// Test parameter.
		AbstractWorkerActor *actor;
//		if (!(actor = dynamic_cast<AbstractWorkerActor *>(cmd->parameter()))) {
//			PERR("Invalid parameter.");
//		}
		// Add to waiting queue.
		_parent->enqueue(actor);
	} else if (cmd->command() == TLVCommand::SHUTDOWN) {
		PINFO_2("Ending runner.");
		_done = true;
	} else {
		PERR("Unexpected command \"" <<
				TLVCommand::CommandString[cmd->command()] << "\".");
	}
}

}
