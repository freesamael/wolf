/**
 * \file CTlvCommandCreator.cpp
 * \date Mar 29, 2010
 * \author samael
 */

#include "CTlvCommandCreator.h"

#include <cstring>
#include <arpa/inet.h>
#include "CTlvBlock.h"
#include "CTlvUint16.h"
#include "CTlvObjectFactory.h"
#include "WfeTLVTypes.h"

using namespace std;

namespace wolf
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
	CTlvCommand *cmd = new CTlvCommand((CTlvCommand::Command)(blk.type() -
			TLV_TYPE_COMMAND_BASE));

	// Construct parameters (if any).
	uint32_t offset = 0;
	while (offset < blk.length()) {
		CSharedTlvBlock pamblk(blk.value() + offset);
		offset += pamblk.plainSize();
		cmd->addParameter(CTlvObjectFactory::instance()->createTLVObject(pamblk));
	}

	return cmd;
}

}
