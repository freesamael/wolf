/**
 * \file TLVCommandTestSuite.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include "HostAddress.h"
#include "TLVCommandTestSuite.h"
#include "TLVCommand.h"
#include "TLVCommandCreator.h"
#include "TLVBlock.h"
#include "WfeTLVTypes.h"
#include "TLVUInt32.h"
#include "TLVUInt16.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVCommandTestSuite);

using namespace cml;
using namespace wfe;

void TLVCommandTestSuite::testToTLVBlock()
{
	TLVCommand *cmd = new TLVCommand();
	ITLVBlock *blk = cmd->toTLVBlock();
	CPPUNIT_ASSERT_EQUAL((uint16_t)TLV_TYPE_COMMAND_BASE, blk->type());
	CPPUNIT_ASSERT_EQUAL((uint16_t)0, blk->length());
	delete blk;
	delete cmd;

	cmd = new TLVCommand(TLVCommand::RUNNER_ADD);
	TLVUInt32 u32_1((uint32_t)HostAddress("192.168.1.1").toInetAddr());
	TLVUInt32 u32_2((uint32_t)HostAddress("192.168.1.2").toInetAddr());
	cmd->addParameter(&u32_1);
	cmd->addParameter(&u32_2);
	blk = cmd->toTLVBlock();
	CPPUNIT_ASSERT_EQUAL((uint16_t)(TLV_TYPE_COMMAND_BASE + TLVCommand::RUNNER_ADD), blk->type());
	CPPUNIT_ASSERT_EQUAL((uint16_t)(TLVUInt32::Size * 2), blk->length());
	delete blk;
	delete cmd;
}
