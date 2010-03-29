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

void TLVMessage::run()
{
	switch (_cmd) {
	case INVALID:
		fprintf(stderr, "TLVMessage::run(): Error: INVALID command can not be run.\n");
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

}
