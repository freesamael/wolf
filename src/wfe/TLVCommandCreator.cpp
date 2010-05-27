/**
 * \file TLVCommandCreator.cpp
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
#include "TLVCommandCreator.h"
#include "WfeTLVTypes.h"

using namespace std;
using namespace cml;

namespace wfe
{

/*
 * The nested TLV blocks look like:\n
 * -----------------------------------\n
 * |    |      | ----(Optional)----- |\n
 * |Type|Length| |Type|Length|Value| |\n
 * |    |      | ------------------- |\n
 * -----------------------------------\n
 * The sub-TLV represents parameter (which is an optional field).
 */
ITLVObject* TLVCommandCreator::create(const ITLVBlock &blk) const
{
	SharedTLVBlock *paramblk;
	ITLVObject *param = NULL;

	// Construct param block (if any).
	if (blk.length() > 0) {
		paramblk = new SharedTLVBlock(blk.value());
		param = TLVObjectFactory::instance()->createTLVObject(*paramblk);
		delete paramblk;
	}

	// Construct message object.
	PINFO("Got TLVCommand with command = " <<
			TLVCommand::CommandString[blk.type() - TLV_TYPE_COMMAND_BASE]);
	TLVCommand *msg = new TLVCommand(blk.type() - TLV_TYPE_COMMAND_BASE, param);

	return msg;
}

}
