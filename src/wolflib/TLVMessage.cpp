/*
 * TLVMessage.cpp
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#include <cstdio>
#include <vector>
#include "TLVMessage.h"
#include "TLVBlock.h"
#include "TLVUInt32.h"

using namespace cml;
using namespace std;

namespace wfe
{

const unsigned short TLVMessage::EMPTY = 0;
const unsigned short TLVMessage::ADD_MASTER = 1;
const unsigned short TLVMessage::ADD_SLAVE = 2;
const unsigned short TLVMessage::RUN_ACTOR = 3;

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
	if (_param) {
		// Create TLV blocks.
		TLVBlock *cmd = TLVUInt32(_cmd).toTLVBlock(),
				*param = _param->toTLVBlock();

		// Put into vector.
		vector<TLVBlock *> blks;
		blks.push_back(cmd);
		blks.push_back(param);

		// Construct concatenated block.
		TLVBlock *blk = TLVBlock::concate(blks);

		// Clean up.
		delete cmd;
		delete param;

		return blk;
	}

	fprintf(stderr, "TLVMessage::toTLVBlock(): Error: Parameter can not be NULL.\n");
	return NULL;
}

}
