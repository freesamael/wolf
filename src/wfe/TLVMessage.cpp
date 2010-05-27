/**
 * \file TLVMessage.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <cstring>
#include <vector>
#include <typeinfo>
#include <TLVBlock.h>
#include <TLVUInt16.h>
#include <TLVObjectFactoryAutoRegistry.h>
#include "TLVMessage.h"
#include "TLVMessageCreator.h"
#include "WfeTLVTypes.h"
#include "HelperMacros.h"

using namespace cml;
using namespace std;

namespace wfe
{

TLV_OBJECT_REGISTRATION(TLVMessage, TLV_TYPE_MESSAGE_BASE + TLVMessage::EMPTY,
		TLVMessageCreator);
TLV_OBJECT_REGISTRATION(TLVMessage, TLV_TYPE_MESSAGE_BASE + TLVMessage::SHUTDOWN,
		TLVMessageCreator);
TLV_OBJECT_REGISTRATION(TLVMessage, TLV_TYPE_MESSAGE_BASE + TLVMessage::HELLO_MASTER,
		TLVMessageCreator);
TLV_OBJECT_REGISTRATION(TLVMessage, TLV_TYPE_MESSAGE_BASE + TLVMessage::HELLO_RUNNER,
		TLVMessageCreator);
TLV_OBJECT_REGISTRATION(TLVMessage, TLV_TYPE_MESSAGE_BASE + TLVMessage::ACTOR_RUN,
		TLVMessageCreator);
TLV_OBJECT_REGISTRATION(TLVMessage, TLV_TYPE_MESSAGE_BASE + TLVMessage::ACTOR_FINISHED,
		TLVMessageCreator);
TLV_OBJECT_REGISTRATION(TLVMessage, TLV_TYPE_MESSAGE_BASE + TLVMessage::RUNNER_ADD,
		TLVMessageCreator);
TLV_OBJECT_REGISTRATION(TLVMessage, TLV_TYPE_MESSAGE_BASE + TLVMessage::RUNNER_START,
		TLVMessageCreator);

const string TLVMessage::CommandString[] = {
		"Empty", "Shutdown", "Hello Master", "Hello Slave",
		"Actor Run", "Actor Finished"
};

/// Empty command.
const uint16_t TLVMessage::EMPTY = 0;

/// Shutdown the runner.
const uint16_t TLVMessage::SHUTDOWN = 1;

/// Hello message from the master node.
const uint16_t TLVMessage::HELLO_MASTER = 2;

/// Hello message from a runner.
const uint16_t TLVMessage::HELLO_RUNNER = 3;

/// Send an actor to a runner and run it.
const uint16_t TLVMessage::ACTOR_RUN = 4;

/// Send an finished actor back.
const uint16_t TLVMessage::ACTOR_FINISHED = 5;

/// Ask a runner to connect to another runner.
const uint16_t TLVMessage::RUNNER_ADD = 6;

/// Tell the runner to start working, which also indicates the runner stop
/// waiting for connections from other runners.
const uint16_t TLVMessage::RUNNER_START = 7;

StandardTLVBlock* TLVMessage::toTLVBlock() const
{
	StandardTLVBlock *blk, *param = NULL;

	// Create param block (if any).
	if (_param) {
		param = _param->toTLVBlock();
		blk = new StandardTLVBlock(TLV_TYPE_MESSAGE_BASE + _cmd,
				param->plainSize());
		memcpy(blk->value(), param->plainBuffer(), blk->length());
	} else {
		blk = new StandardTLVBlock(TLV_TYPE_MESSAGE_BASE + _cmd);
	}

	// Clean up.
	delete param;

	return blk;
}

}
