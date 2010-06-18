/**
 * \file MasterSideCommandListener.cpp
 * \date Jun 3, 2010
 * \author samael
 */

#include "HelperMacros.h"
#include "TLVUInt32.h"
#include "MasterSideCommandListener.h"

using namespace cml;

namespace wfe
{

void MasterSideCommandListener::process(TLVCommand *cmd)
{
	if (cmd->command() == TLVCommand::WORKER_FINISHED) {
		PINF_2("Got command WORKER_FINISHED.");
		TLVUInt32 *u32;
		AbstractWorkerActor *worker;
		if (cmd->parameters().size() != 2) { // [id, worker]
			PERR("Invalid number of parameters.");
			return;
		}
		if (!(u32 = dynamic_cast<TLVUInt32 *>(cmd->parameters()[0]))) {
			PERR("Invalid parameter.");
			return;
		}
		if (!(worker = dynamic_cast<AbstractWorkerActor *>(cmd->parameters()[1]))) {
			PERR("Invalid parameter.");
			delete u32;
			return;
		}
		_master->workerFinished(u32->value(), *worker);
		delete u32;
		delete worker;
	} else {
		PERR("Unexpected command \"" <<
				TLVCommand::CommandString[cmd->command()] << "\".");
	}
}

}
