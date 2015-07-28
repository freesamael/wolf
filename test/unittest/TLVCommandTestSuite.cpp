/**
 * \file TLVCommandTestSuite.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include "CHostAddress.h"
#include "TLVCommandTestSuite.h"
#include "CTlvCommand.h"
#include "CTlvCommandCreator.h"
#include "CTlvBlock.h"
#include "WfeTLVTypes.h"
#include "CTlvUint32.h"
#include "CTlvUint16.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVCommandTestSuite);

using namespace wolf;
using namespace wolf;

void TLVCommandTestSuite::testToTLVBlock()
{
	CTlvCommand *cmd = new CTlvCommand();
	ITlvBlock *blk = cmd->toTLVBlock();
	CPPUNIT_ASSERT_EQUAL((uint32_t)TLV_TYPE_COMMAND_BASE, blk->type());
	CPPUNIT_ASSERT_EQUAL((uint32_t)0, blk->length());
	delete blk;
	delete cmd;

	cmd = new CTlvCommand(CTlvCommand::RUNNER_ADD);
	CTlvUint32 u32_1((uint32_t)CHostAddress("192.168.1.1").toInetAddr());
	CTlvUint32 u32_2((uint32_t)CHostAddress("192.168.1.2").toInetAddr());
	cmd->addParameter(&u32_1);
	cmd->addParameter(&u32_2);
	blk = cmd->toTLVBlock();
	CPPUNIT_ASSERT_EQUAL((uint32_t)(TLV_TYPE_COMMAND_BASE + CTlvCommand::RUNNER_ADD), blk->type());
	CPPUNIT_ASSERT_EQUAL((uint32_t)(CTlvUint32::Size * 2), blk->length());
	delete blk;
	delete cmd;
}
