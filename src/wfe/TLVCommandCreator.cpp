/**
 * \file TLVCommandCreator.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include "TLVBlock.h"
#include "TLVUInt16.h"
#include "TLVObjectFactory.h"
#include "HelperMacros.h"
#include "TLVCommandCreator.h"
#include "WfeTLVTypes.h"

using namespace std;
using namespace cml;

namespace wfe
{

/*
 * The nested TLV blocks look like:\n
 * --------------------------------------\n
 * |    |      | ----(Optional)-----    |\n
 * |Type|Length| |Type|Length|Value| ...|\n
 * |    |      | -------------------    |\n
 * --------------------------------------\n
 * The sub-TLVs represent parameters (which are optional).
 */
ITLVObject* TLVCommandCreator::create(const ITLVBlock &blk) const
{
	PINFO("Got TLVCommand with command = " <<
			TLVCommand::CommandString[blk.type() - TLV_TYPE_COMMAND_BASE]);

	TLVCommand *cmd = new TLVCommand(blk.type() - TLV_TYPE_COMMAND_BASE);

	// Construct parameters (if any).
	if (blk.length() > 0) {
		unsigned short offset = 0;
		do {
			SharedTLVBlock pamblk(blk.plainBuffer() + offset);
			offset += pamblk.plainSize();
			cmd->addParameter(TLVObjectFactory::instance()->createTLVObject(pamblk));
		} while (offset < blk.length());
	}

	return cmd;
}

}
