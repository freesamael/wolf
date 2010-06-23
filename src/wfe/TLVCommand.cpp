/**
 * \file TLVCommand.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <cstring>
#include <vector>
#include <typeinfo>
#include "TLVBlock.h"
#include "TLVUInt16.h"
#include "TLVObjectFactoryAutoRegistry.h"
#include "TLVCommand.h"
#include "TLVCommandCreator.h"
#include "WfeTLVTypes.h"
#include "HelperMacros.h"

using namespace cml;
using namespace std;

namespace wfe
{

TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::EMPTY,
		TLVCommandCreator);
TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::SHUTDOWN,
		TLVCommandCreator);
TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::HELLO_MASTER,
		TLVCommandCreator);
TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::HELLO_RUNNER,
		TLVCommandCreator);
TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::WORKER_RUN,
		TLVCommandCreator);
TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::WORKER_STEAL,
		TLVCommandCreator);
TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::WORKER_STEAL_FAILED,
		TLVCommandCreator);
TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::WORKER_FINISHED,
		TLVCommandCreator);
TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::RUNNER_ADD,
		TLVCommandCreator);
TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::RUNNER_START,
		TLVCommandCreator);

const string TLVCommand::CommandString[] = {
		"EMPTY", "SHUTDOWN", "HELLO_MASTER", "HELLO_RUNNER", "WORKER_RUN",
		"WORKER_STEAL", "WORKER_STEAL_FAILED", "WORKER_FINISHED", "RUNNER_ADD",
		"RUNNER_START"
};

TLVCommand::~TLVCommand()
{
	if (_autoclean) {
		for (unsigned i = 0; i < _params.size(); i++)
			delete _params[i];
	}
}

StandardTLVBlock* TLVCommand::toTLVBlock() const
{
	StandardTLVBlock *blk;

	if (_params.size() > 0) { 	// Create param block (if any).
		vector<const ITLVBlock *> pamblks;
		for (unsigned i = 0; i < _params.size(); i++)
			pamblks.push_back(_params[i]->toTLVBlock());
		blk = StandardTLVBlock::concate(pamblks);
		blk->setType(TLV_TYPE_COMMAND_BASE + _cmd);
		// Clean up.
		for (unsigned i = 0; i < pamblks.size(); i++)
			delete pamblks[i];
	} else {
		blk = new StandardTLVBlock((uint16_t)(TLV_TYPE_COMMAND_BASE + _cmd));
	}

	return blk;
}

}
