/**
 * \file MasterSideCommandListener.cpp
 * \date Jun 3, 2010
 * \author samael
 */

#include "HelperMacros.h"
#include "TLVReaderWriter.h"
#include "TLVUInt32.h"
#include "MasterSideCommandListener.h"

using namespace cml;

namespace wfe
{

void MasterSideCommandListener::run()
{
	TLVReaderWriter tcprw(_rsock);
	ITLVObject *inobj;
	TLVCommand *incmd = NULL;

	PINFO_2("Start listening for runner commands.");
	while (!_done) {
		if (!(inobj = tcprw.read()))
			break; // End of file.
		if (!(incmd = dynamic_cast<TLVCommand *>(inobj))) {
			PERR("Invalid incoming message.");
			delete inobj;
		} else {
			process(incmd);
			delete incmd;
		}
	}
	PINFO_2("Running loop ends.");
}

void MasterSideCommandListener::process(TLVCommand *cmd)
{
	PINFO_2("Processing a command.");
	if (cmd->command() == TLVCommand::WORKER_FINISHED) {
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
