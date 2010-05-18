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
TLV_OBJECT_REGISTRATION(TLVMessage, TLV_TYPE_MESSAGE_BASE + TLVMessage::HELLO_SLAVE,
		TLVMessageCreator);
TLV_OBJECT_REGISTRATION(TLVMessage, TLV_TYPE_MESSAGE_BASE + TLVMessage::ACTOR_RUN,
		TLVMessageCreator);
TLV_OBJECT_REGISTRATION(TLVMessage, TLV_TYPE_MESSAGE_BASE + TLVMessage::ACTOR_FINISHED,
		TLVMessageCreator);

const string TLVMessage::CommandString[] = {
		"Empty", "Shutdown", "Hello Master", "Hello Slave",
		"Actor Run", "Actor Finished"
};
const uint16_t TLVMessage::EMPTY = 0;
const uint16_t TLVMessage::SHUTDOWN = 1;
const uint16_t TLVMessage::HELLO_MASTER = 2;
const uint16_t TLVMessage::HELLO_SLAVE = 3;
const uint16_t TLVMessage::ACTOR_RUN = 4;
const uint16_t TLVMessage::ACTOR_FINISHED = 5;

StandardTLVBlock* TLVMessage::toTLVBlock() const
{
	StandardTLVBlock *blk, *param = NULL;

	// Create param block (if any).
	if (_param) {
		param = _param->toTLVBlock();
		blk = new StandardTLVBlock(param->plainSize());
		memcpy(blk->value(), param->plainBuffer(), blk->length());
	} else {
		blk = new StandardTLVBlock();
	}
	blk->setType(TLV_TYPE_MESSAGE_BASE + _cmd);

	// Clean up.
	delete param;

	return blk;
}

}
