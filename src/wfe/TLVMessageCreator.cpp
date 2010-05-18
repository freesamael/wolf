/**
 * \file TLVMessageCreator.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <TLVBlock.h>
#include <TLVUInt16.h>
#include <TLVObjectFactory.h>
#include <HelperMacros.h>
#include "TLVMessageCreator.h"
#include "WfeTLVTypes.h"

using namespace std;
using namespace cml;

namespace wfe
{

/*
 * The nested TLV blocks look like:\n
 * -------------------------------------------------------\n
 * |    |      | ------------------- ----(Optional)----- |\n
 * |Type|Length| |Type|Length|Value| |Type|Length|Value| |\n
 * |    |      | ------------------- ------------------- |\n
 * -------------------------------------------------------\n
 * The first sub-TLV is command, and the second represents parameter (which is
 * an optional field).
 */
ITLVObject* TLVMessageCreator::create(const ITLVBlock &blk) const
{
	SharedTLVBlock *cmdblk, *paramblk;
	TLVUInt16 *cmd;
	ITLVObject *param = NULL;

	// Construct command block.
	cmdblk = new SharedTLVBlock(blk.value());
	cmd = dynamic_cast<TLVUInt16 *>(TLVObjectFactory::instance()->
			createTLVObject(*cmdblk));
	if (!cmd) {
		PERR("Unable to construct command.");
		return NULL;
	}

	// Construct param block (if any).
	if (blk.length() > TLVUInt16::Size) {
		paramblk = new SharedTLVBlock(blk.value() + cmdblk->plainSize());
		param = TLVObjectFactory::instance()->createTLVObject(*paramblk);
		delete paramblk;
	}

	// Construct message object.
	PINFO("Got TLVMessage with command = " <<
			TLVMessage::CommandString[blk.type() - TLV_TYPE_MESSAGE_BASE]);
	TLVMessage *msg = new TLVMessage(blk.type() - TLV_TYPE_MESSAGE_BASE, param);

	delete cmd;
	delete cmdblk;

	return msg;
}

}
