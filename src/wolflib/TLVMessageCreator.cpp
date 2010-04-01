/*
 * TLVMessageCreator.cpp
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#include <cstdio>
#include <cstring>
#include <arpa/inet.h>
#include <TLVBlock.h>
#include <TLVUInt16.h>
#include <TLVObjectFactory.h>
#include "TLVMessageCreator.h"

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
ITLVObject* TLVMessageCreator::create(const ITLVBlock &blk) const
{
	SharedTLVBlock *cmdblk, *paramblk;
	TLVUInt16 *cmd;
	ITLVObject *param = NULL;

	// Construct command block.
	cmdblk = new SharedTLVBlock(blk.getValueBuffer());
	cmd = dynamic_cast<TLVUInt16 *>(TLVObjectFactory::instance()->
			createTLVObject(*cmdblk));
	if (!cmd) {
		fprintf(stderr, "TLVMessageCreator::create(): Error: Unable to construct command.\n");
		return NULL;
	}

	// Construct param block (if any).
	if (blk.length() > TLVUInt16::Size) {
		paramblk = new SharedTLVBlock(blk.getValueBuffer() + cmdblk->size());
		param = TLVObjectFactory::instance()->createTLVObject(*paramblk);
		delete paramblk;
	}

	// Construct message object.
	TLVMessage *msg = new TLVMessage(cmd->value(), param);

	delete cmd;
	delete cmdblk;

	return msg;
}

}
