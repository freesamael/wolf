/*
 * TLVMessageCreator.cpp
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#include <cstdio>
#include <cstring>
#include <arpa/inet.h>
#include "TLVMessageCreator.h"
#include "TLVBlock.h"
#include "TLVUInt16.h"
#include "TLVObjectFactory.h"

using namespace cml;

namespace wfe
{

/**
 * @detailed The nested TLV blocks look like:
 * -------------------------------------------------------
 * |    |      | ------------------- ----(Optional)----- |
 * |Type|Length| |Type|Length|Value| |Type|Length|Value| |
 * |    |      | ------------------- ------------------- |
 * -------------------------------------------------------
 * The first sub-TLV is command, and the second represents parameter (which is
 * an optional field).
 */
ITLVObject* TLVMessageCreator::create(const TLVBlock &blk) const
{
	TLVBlock cmdblk, paramblk;
	TLVUInt16 *cmd = NULL;
	ITLVObject *param = NULL;

	// Construct command block.
//	unsigned short *ntype = (unsigned short *)blk.getValueBuffer();
//	unsigned short *nlen = (unsigned short *)&blk.getValueBuffer()[TLVBlock::szType];
//	cmdblk.setType(ntohs(*ntype));
//	cmdblk.setLength(ntohs(*nlen));
//	memcpy(cmdblk.getValueBuffer(), &blk.getValueBuffer()[TLVBlock::szHeader],
//			cmdblk.length());
	cmd = dynamic_cast<TLVUInt16 *>(TLVObjectFactory::instance()->
			createTLVObject(*((TLVBlock *)blk.getValueBuffer())));
	if (!cmd) {
		fprintf(stderr, "TLVMessageCreator::create(): Error: Unable to construct command.\n");
		return NULL;
	}

	// Construct param block (if any).
	if (blk.length() > ((TLVBlock*)blk.getValueBuffer())->size() ) {
//		ntype = (unsigned short *)&blk.getValueBuffer()[cmdblk.size()];
//		nlen = (unsigned short *)&blk.getValueBuffer()[cmdblk.size() + TLVBlock::szType];
//		paramblk.setType(ntohs(*ntype));
//		paramblk.setLength(ntohs(*nlen));
//		memcpy(paramblk.getValueBuffer(),
//				&blk.getValueBuffer()[cmdblk.size() + TLVBlock::szHeader],
//				paramblk.length());
		param = TLVObjectFactory::instance()->
				createTLVObject(*((TLVBlock *)(blk.getValueBuffer() +
						((TLVBlock*)blk.getValueBuffer())->size())));
	}

	// Construct message object.
	TLVMessage *msg = new TLVMessage(cmd->value(), param);
	delete cmd;

	return msg;
}

}
