/**
 * \file TLVCommandTestSuite.cpp
 * \date Mar 30, 2010
 * \author samael
 */

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
	TLVCommand msg(TLVCommand::HELLO_MASTER);
	StandardTLVBlock *blk = msg.toTLVBlock();

	CPPUNIT_ASSERT_EQUAL((uint16_t)(TLV_TYPE_COMMAND_BASE +
			TLVCommand::HELLO_MASTER), blk->type());
	CPPUNIT_ASSERT_EQUAL((uint16_t)0, blk->length());

	delete blk;

	TLVUInt32 *u32 = new TLVUInt32(2048);
	msg.setParameter(u32);
	blk = msg.toTLVBlock();

	CPPUNIT_ASSERT_EQUAL(TLVUInt32::Size, blk->length());

	delete u32;
	delete blk;
}
