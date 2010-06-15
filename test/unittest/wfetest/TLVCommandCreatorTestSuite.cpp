/**
 * \file TLVCommandCreatorTestSuite.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include "HostAddress.h"
#include "TLVCommandCreatorTestSuite.h"
#include "TLVCommandCreator.h"
#include "TLVCommand.h"
#include "TLVBlock.h"
#include "TLVUInt32.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVCommandCreatorTestSuite);

using namespace cml;
using namespace wfe;

void TLVCommandCreatorTestSuite::testCreate()
{
	TLVCommand cmd(TLVCommand::RUNNER_ADD);
	TLVUInt32 u32_1((uint32_t)HostAddress("192.168.2.1").toInetAddr());
	TLVUInt32 u32_2((uint32_t)HostAddress("192.168.2.2").toInetAddr());
	TLVUInt32 u32_3((uint32_t)HostAddress("192.168.2.3").toInetAddr());
	cmd.addParameter(&u32_1);
	cmd.addParameter(&u32_2);
	cmd.addParameter(&u32_3);

	StandardTLVBlock *blk = cmd.toTLVBlock();
	CPPUNIT_ASSERT_EQUAL((uint16_t)(TLVUInt32::Size * 3), blk->length());
	TLVCommand *ocmd = (TLVCommand *)TLVCommandCreator().create(*blk);
	CPPUNIT_ASSERT_EQUAL(TLVCommand::RUNNER_ADD, ocmd->command());
	CPPUNIT_ASSERT_EQUAL((size_t)3, ocmd->parameters().size());
	CPPUNIT_ASSERT_EQUAL(HostAddress("192.168.2.1").toString(),
			HostAddress((in_addr_t)((TLVUInt32 *)ocmd->parameters()[0])->value()).toString());
	CPPUNIT_ASSERT_EQUAL(HostAddress("192.168.2.2").toString(),
			HostAddress((in_addr_t)((TLVUInt32 *)ocmd->parameters()[1])->value()).toString());
	CPPUNIT_ASSERT_EQUAL(HostAddress("192.168.2.3").toString(),
			HostAddress((in_addr_t)((TLVUInt32 *)ocmd->parameters()[2])->value()).toString());

	delete blk;
	delete ocmd->parameters()[0];
	delete ocmd->parameters()[1];
	delete ocmd->parameters()[2];
	delete ocmd;
}
