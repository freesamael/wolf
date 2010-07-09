/**
 * \file CTlvCommand.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <cstring>
#include <vector>
#include <typeinfo>
#include "CTlvBlock.h"
#include "CTlvUint16.h"
#include "CTlvObjectFactoryAutoRegistry.h"
#include "CTlvCommand.h"
#include "CTlvCommandCreator.h"
#include "WfeTLVTypes.h"
#include "HelperMacros.h"

using namespace cml;
using namespace std;

namespace wfe
{

TLV_OBJECT_REGISTRATION(CTlvCommand, TLV_TYPE_COMMAND_BASE + CTlvCommand::EMPTY,
		CTlvCommandCreator);
TLV_OBJECT_REGISTRATION(CTlvCommand, TLV_TYPE_COMMAND_BASE + CTlvCommand::SHUTDOWN,
		CTlvCommandCreator);
TLV_OBJECT_REGISTRATION(CTlvCommand, TLV_TYPE_COMMAND_BASE + CTlvCommand::HELLO_MASTER,
		CTlvCommandCreator);
TLV_OBJECT_REGISTRATION(CTlvCommand, TLV_TYPE_COMMAND_BASE + CTlvCommand::HELLO_RUNNER,
		CTlvCommandCreator);
TLV_OBJECT_REGISTRATION(CTlvCommand, TLV_TYPE_COMMAND_BASE + CTlvCommand::WORKER_RUN,
		CTlvCommandCreator);
TLV_OBJECT_REGISTRATION(CTlvCommand, TLV_TYPE_COMMAND_BASE + CTlvCommand::WORKER_STEAL,
		CTlvCommandCreator);
TLV_OBJECT_REGISTRATION(CTlvCommand, TLV_TYPE_COMMAND_BASE + CTlvCommand::WORKER_STEAL_FAILED,
		CTlvCommandCreator);
TLV_OBJECT_REGISTRATION(CTlvCommand, TLV_TYPE_COMMAND_BASE + CTlvCommand::WORKER_FINISHED,
		CTlvCommandCreator);
TLV_OBJECT_REGISTRATION(CTlvCommand, TLV_TYPE_COMMAND_BASE + CTlvCommand::RUNNER_ADD,
		CTlvCommandCreator);
TLV_OBJECT_REGISTRATION(CTlvCommand, TLV_TYPE_COMMAND_BASE + CTlvCommand::RUNNER_START,
		CTlvCommandCreator);

const string CTlvCommand::CommandString[] = {
		"EMPTY", "SHUTDOWN", "HELLO_MASTER", "HELLO_RUNNER", "WORKER_RUN",
		"WORKER_STEAL", "WORKER_STEAL_FAILED", "WORKER_FINISHED", "RUNNER_ADD",
		"RUNNER_START"
};

CTlvCommand::~CTlvCommand()
{
	if (_autoclean) {
		for (unsigned i = 0; i < _params.size(); i++)
			delete _params[i];
	}
}

CTlvBlock* CTlvCommand::toTLVBlock() const
{
	CTlvBlock *blk;

	if (_params.size() > 0) { 	// Create param block (if any).
		vector<const ITlvBlock *> pamblks;
		for (unsigned i = 0; i < _params.size(); i++)
			pamblks.push_back(_params[i]->toTLVBlock());
		blk = CTlvBlock::concate(pamblks);
		blk->setType(TLV_TYPE_COMMAND_BASE + _cmd);
		// Clean up.
		for (unsigned i = 0; i < pamblks.size(); i++)
			delete pamblks[i];
	} else {
		blk = new CTlvBlock((uint16_t)(TLV_TYPE_COMMAND_BASE + _cmd));
	}

	return blk;
}

}
