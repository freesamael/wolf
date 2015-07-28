/**
 * \file TLVCommandCreatorTestSuite.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include "CHostAddress.h"
#include "TLVCommandCreatorTestSuite.h"
#include "CTlvCommandCreator.h"
#include "CTlvCommand.h"
#include "CTlvBlock.h"
#include "CTlvUint32.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVCommandCreatorTestSuite);

using namespace wolf;
using namespace wolf;

void TLVCommandCreatorTestSuite::testCreate()
{
	CTlvCommand cmd(CTlvCommand::RUNNER_ADD);
	CTlvUint32 u32_1((uint32_t)CHostAddress("192.168.2.1").toInetAddr());
	CTlvUint32 u32_2((uint32_t)CHostAddress("192.168.2.2").toInetAddr());
	CTlvUint32 u32_3((uint32_t)CHostAddress("192.168.2.3").toInetAddr());
	cmd.addParameter(&u32_1);
	cmd.addParameter(&u32_2);
	cmd.addParameter(&u32_3);

	CTlvBlock *blk = cmd.toTLVBlock();
	CPPUNIT_ASSERT_EQUAL((uint32_t)(CTlvUint32::Size * 3), blk->length());
	CTlvCommand *ocmd = (CTlvCommand *)CTlvCommandCreator().create(*blk);
	CPPUNIT_ASSERT_EQUAL(CTlvCommand::RUNNER_ADD, ocmd->command());
	CPPUNIT_ASSERT_EQUAL((size_t)3, ocmd->parameters().size());
	CPPUNIT_ASSERT_EQUAL(CHostAddress("192.168.2.1").toString(),
			CHostAddress((in_addr_t)((CTlvUint32 *)ocmd->parameters()[0])->value()).toString());
	CPPUNIT_ASSERT_EQUAL(CHostAddress("192.168.2.2").toString(),
			CHostAddress((in_addr_t)((CTlvUint32 *)ocmd->parameters()[1])->value()).toString());
	CPPUNIT_ASSERT_EQUAL(CHostAddress("192.168.2.3").toString(),
			CHostAddress((in_addr_t)((CTlvUint32 *)ocmd->parameters()[2])->value()).toString());

	delete blk;
	delete ocmd->parameters()[0];
	delete ocmd->parameters()[1];
	delete ocmd->parameters()[2];
	delete ocmd;
}
