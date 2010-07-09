/**
 * \file CTlvCommandCreator.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include "CTlvBlock.h"
#include "CTlvUint16.h"
#include "CTlvObjectFactory.h"
#include "HelperMacros.h"
#include "CTlvCommandCreator.h"
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
ITlvObject* CTlvCommandCreator::create(const ITlvBlock &blk) const
{
	PINF_2("Got TLVCommand with command = " <<
			CTlvCommand::CommandString[blk.type() - TLV_TYPE_COMMAND_BASE]);

	CTlvCommand *cmd = new CTlvCommand((CTlvCommand::Command)(blk.type() -
			TLV_TYPE_COMMAND_BASE));

	// Construct parameters (if any).
	unsigned short offset = 0;
	while (offset < blk.length()) {
		CSharedTlvBlock pamblk(blk.value() + offset);
		offset += pamblk.plainSize();
		PINF_2("Got a parameter block with type = " << pamblk.type() <<
				", length = " << pamblk.length());
		cmd->addParameter(CTlvObjectFactory::instance()->createTLVObject(pamblk));
	}

	return cmd;
}

}
