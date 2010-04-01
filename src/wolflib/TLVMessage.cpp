/*
 * TLVMessage.cpp
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#include <cstdio>
#include <vector>
#include <typeinfo>
#include "TLVMessage.h"
#include "TLVBlock.h"
#include "TLVUInt16.h"
#include "TLVObjectFactory.h"
#include "CustomTLVTypes.h"

using namespace cml;
using namespace std;

namespace wfe
{

const unsigned short TLVMessage::TLVType = 10;

const char *TLVMessage::CommandString[] = {
		"Empty", "Add Master", "Add Slave", "Run Actor", "Shutdown"
};
const unsigned short TLVMessage::EMPTY = 0;
const unsigned short TLVMessage::ADD_MASTER = 1;
const unsigned short TLVMessage::ADD_SLAVE = 2;
const unsigned short TLVMessage::RUN_ACTOR = 3;
const unsigned short TLVMessage::SHUTDOWN = 4;

void TLVMessage::run()
{
	switch (_cmd) {
	case EMPTY:
		fprintf(stderr, "TLVMessage::run(): Error: EMPTY command can not be run.\n");
		break;
	case ADD_MASTER:
		break;
	case ADD_SLAVE:
		break;
	case RUN_ACTOR:
		break;
	default:
		fprintf(stderr, "TLVMessage::run(): Error: Unrecognized command.\n");
	}
}

TLVBlock* TLVMessage::toTLVBlock() const
{
	vector<const ITLVBlock *> blks;
	TLVBlock *cmd = NULL, *param = NULL;

	// Create command block.
	cmd = TLVUInt16(_cmd).toTLVBlock();
	blks.push_back(cmd);

	// Create param block (if any).
	if (_param) {
		param = _param->toTLVBlock();
		blks.push_back(param);
	}

	// Construct concatenated block.
	TLVBlock *blk = TLVBlock::concate(blks);
	blk->setType(TLV_TYPE_MESSAGE);

	// Clean up.
	delete cmd;
	delete param;

	return blk;
}

}
