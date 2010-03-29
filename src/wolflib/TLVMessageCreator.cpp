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
 * |    |      | ------------------- ------------------- |
 * |Type|Length| |Type|Length|Value| |Type|Length|Value| |
 * |    |      | ------------------- ------------------- |
 * -------------------------------------------------------
 * Where the first sub-TLV is command, and the second represents parameter.
 */
ITLVObject* TLVMessageCreator::create(const TLVBlock &blk)
{
	TLVBlock cmdblk, paramblk;

	// Construct command block.
	unsigned short *ntype = (unsigned short *)blk.getValueBuffer();
	unsigned short *nlen = (unsigned short *)&blk.getValueBuffer()[TLVBlock::szType];
	cmdblk.setType(ntohs(*ntype));
	cmdblk.setLength(ntohs(*nlen));
	memcpy(cmdblk.getValueBuffer(), &blk.getValueBuffer()[TLVBlock::szHeader],
			cmdblk.length());
	TLVUInt16 *cmd = dynamic_cast<TLVUInt16 *>(TLVObjectFactory::instance()->
			createTLVObject(cmdblk));
	if (!cmd) {
		fprintf(stderr, "TLVMessageCreator::create(): Error: Unable to construct command.\n");
		return NULL;
	}

	// Construct param block.
	ntype = (unsigned short *)&blk.getValueBuffer()[cmdblk.size()];
	nlen = (unsigned short *)&blk.getValueBuffer()[cmdblk.size() + TLVBlock::szType];
	paramblk.setType(ntohs(*ntype));
	paramblk.setLength(ntohs(*nlen));
	memcpy(paramblk.getValueBuffer(),
			&blk.getValueBuffer()[cmdblk.size() + TLVBlock::szHeader],
			paramblk.length());
	ITLVObject *param = TLVObjectFactory::instance()->createTLVObject(paramblk);
	if (!param) {
		fprintf(stderr, "TLVMessageCreator::create(): Error: Unable to construct parameter.\n");
		return NULL;
	}

	// Construct message object.
	TLVMessage *msg = new TLVMessage(cmd->value(), param);
	delete cmd;

	return msg;
}

}
