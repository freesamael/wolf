/**
 * \file TLVMessage.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <cstdio>
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

TLV_OBJECT_REGISTRATION(TLVMessage, TLV_TYPE_MESSAGE, TLVMessageCreator);

const uint16_t TLVMessage::TLVType = 10;

const char *TLVMessage::CommandString[] = {
		"Empty", "Shutdown", "Hello Master", "Hello Slave", "Run Actor"
};
const uint16_t TLVMessage::EMPTY = 0;
const uint16_t TLVMessage::SHUTDOWN = 1;
const uint16_t TLVMessage::HELLO_MASTER = 2;
const uint16_t TLVMessage::HELLO_SLAVE = 3;
const uint16_t TLVMessage::RUN_ACTOR = 4;

StandardTLVBlock* TLVMessage::toTLVBlock() const
{
	vector<const ITLVBlock *> blks;
	StandardTLVBlock *cmd = NULL, *param = NULL;

	// Create command block.
	cmd = TLVUInt16(_cmd).toTLVBlock();
	blks.push_back(cmd);

	// Create param block (if any).
	if (_param) {
		param = _param->toTLVBlock();
		blks.push_back(param);
	}

	// Construct concatenated block.
	StandardTLVBlock *blk = StandardTLVBlock::concate(blks);
	blk->setType(TLV_TYPE_MESSAGE);

	// Clean up.
	delete cmd;
	delete param;

	return blk;
}

}
