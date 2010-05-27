/**
 * \file TLVCommandCreatorTestSuite.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include "TLVCommandCreatorTestSuite.h"
#include "TLVCommandCreator.h"
#include "TLVBlock.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVCommandCreatorTestSuite);

using namespace cml;
using namespace wfe;

void TLVCommandCreatorTestSuite::testCreate()
{
	TLVCommandCreator creator;
	TLVCommand msg(TLVCommand::ACTOR_RUN);

	StandardTLVBlock *blk = msg.toTLVBlock();
	TLVCommand *omsg = dynamic_cast<TLVCommand *>(creator.create(*blk));

	CPPUNIT_ASSERT(omsg);
	CPPUNIT_ASSERT_EQUAL(msg.command(), omsg->command());
	CPPUNIT_ASSERT_EQUAL(msg.parameter(), omsg->parameter());

	delete blk;
	delete omsg;
}
