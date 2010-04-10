/*
 * TLVMessage.cpp
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
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

const unsigned short TLVMessage::TLVType = 10;

const char *TLVMessage::CommandString[] = {
		"Empty", "Hello Master", "Hello Slave", "Run Actor", "Shutdown"
};
const unsigned short TLVMessage::EMPTY = 0;
const unsigned short TLVMessage::HELLO_MASTER = 1;
const unsigned short TLVMessage::HELLO_SLAVE = 2;
const unsigned short TLVMessage::RUN_ACTOR = 3;
const unsigned short TLVMessage::SHUTDOWN = 4;

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
