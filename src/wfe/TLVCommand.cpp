/**
 * \file TLVCommand.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <cstring>
#include <vector>
#include <typeinfo>
#include <TLVBlock.h>
#include <TLVUInt16.h>
#include <TLVObjectFactoryAutoRegistry.h>
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
TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::ACTOR_RUN,
		TLVCommandCreator);
TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::ACTOR_FINISHED,
		TLVCommandCreator);
TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::RUNNER_ADD,
		TLVCommandCreator);
TLV_OBJECT_REGISTRATION(TLVCommand, TLV_TYPE_COMMAND_BASE + TLVCommand::RUNNER_START,
		TLVCommandCreator);

const string TLVCommand::CommandString[] = {
		"Empty", "Shutdown", "Hello Master", "Hello Slave",
		"Actor Run", "Actor Finished"
};

/// Empty command.
const uint16_t TLVCommand::EMPTY = 0;

/// Shutdown the runner.
const uint16_t TLVCommand::SHUTDOWN = 1;

/// Hello message from the master node.
const uint16_t TLVCommand::HELLO_MASTER = 2;

/// Hello message from a runner.
const uint16_t TLVCommand::HELLO_RUNNER = 3;

/// Send an actor to a runner and run it.
const uint16_t TLVCommand::ACTOR_RUN = 4;

/// Send an finished actor back.
const uint16_t TLVCommand::ACTOR_FINISHED = 5;

/// Ask a runner to connect to another runner.
const uint16_t TLVCommand::RUNNER_ADD = 6;

/// Tell the runner to start working, which also indicates the runner stop
/// waiting for connections from other runners.
const uint16_t TLVCommand::RUNNER_START = 7;

StandardTLVBlock* TLVCommand::toTLVBlock() const
{
	StandardTLVBlock *blk, *param = NULL;

	// Create param block (if any).
	if (_param) {
		param = _param->toTLVBlock();
		blk = new StandardTLVBlock(TLV_TYPE_COMMAND_BASE + _cmd,
				param->plainSize());
		memcpy(blk->value(), param->plainBuffer(), blk->length());
	} else {
		blk = new StandardTLVBlock(TLV_TYPE_COMMAND_BASE + _cmd);
	}

	// Clean up.
	delete param;

	return blk;
}

}
