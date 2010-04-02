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
#include <TLVObjectFactory.h>
#include "TLVMessage.h"
#include "CustomTLVTypes.h"

using namespace cml;
using namespace std;

namespace wfe
{

const unsigned short TLVMessage::TLVType = 10;

const char *TLVMessage::CommandString[] = {
		"Empty", "Hello Master", "Hello Slave", "Run Actor", "Shutdown"
};
const unsigned short TLVMessage::EMPTY = 0;
const unsigned short TLVMessage::HELLO_MASTER = 1;
const unsigned short TLVMessage::HELLO_SLAVE = 2;
const unsigned short TLVMessage::RUN_ACTOR = 3;
const unsigned short TLVMessage::SHUTDOWN = 4;

void TLVMessage::run()
{
	switch (_cmd) {
	case EMPTY:
		fprintf(stderr, "TLVMessage::run(): Error: EMPTY command can not be run.\n");
		break;
	case HELLO_MASTER:
		break;
	case HELLO_SLAVE:
		break;
	case RUN_ACTOR:
		break;
	default:
		fprintf(stderr, "TLVMessage::run(): Error: Unrecognized command.\n");
	}
}

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
