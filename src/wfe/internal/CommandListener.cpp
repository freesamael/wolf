/**
 * \file CommandListener.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include <iostream>
#include <TLVReaderWriter.h>
#include <HelperMacros.h>
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
	TLVMessage *inmsg = NULL;

	while (!_done) {
		if (!(inobj = tcprw.read()))
			break; // End of file.
		if (!(inmsg = dynamic_cast<TLVMessage *>(inobj))) {
			PERR("Invalid incoming message.");
			delete inobj;
		} else {
			AbstractWorkerActor *actor;
			if ((actor = processCommand(inmsg))) {
				PINFO("Returning finish message.");
				TLVMessage rtn(TLVMessage::ACTOR_FINISHED, actor);
				tcprw.write(rtn);
				delete actor;
			}
			delete inmsg;
		}
	}
	PINFO("CommandListener running loop ends.");
}

/**
 * Process command. Return true if the actor is successfully extracted and
 * executed.
 */
AbstractWorkerActor* CommandListener::processCommand(TLVMessage *cmd)
{
	PINFO("Processing a command.");
	if (cmd->command() == TLVMessage::ACTOR_RUN) {
		// Test parameter.
		AbstractWorkerActor *actor;
		if (!(actor = dynamic_cast<AbstractWorkerActor *>(cmd->parameter()))) {
			PERR("Invalid parameter.");
			return NULL;
		}

		// Run actor.
		actor->setup();
		do {
			actor->prefire();
			actor->fire();
			actor->postfire();
		} while (actor->testfire());
		actor->wrapup();
		return actor;
	} else if (cmd->command() == TLVMessage::SHUTDOWN) {
		PINFO("Ending runner.");
		_done = true;
	} else {
		PERR("Unexpected command \"" <<
				TLVMessage::CommandString[cmd->command()] << "\".");
	}
	return NULL;
}

}
