/**
 * \file TLVMessageCreatorTestSuite.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include "TLVMessageCreatorTestSuite.h"
#include "TLVMessageCreator.h"
#include "TLVBlock.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVMessageCreatorTestSuite);

using namespace cml;
using namespace wfe;

void TLVMessageCreatorTestSuite::testCreate()
{
	TLVMessageCreator creator;
	TLVMessage msg(TLVMessage::RUN_ACTOR);

	StandardTLVBlock *blk = msg.toTLVBlock();
	TLVMessage *omsg = dynamic_cast<TLVMessage *>(creator.create(*blk));

	CPPUNIT_ASSERT(omsg);
	CPPUNIT_ASSERT_EQUAL(msg.command(), omsg->command());
	CPPUNIT_ASSERT_EQUAL(msg.parameter(), omsg->parameter());

	delete blk;
	delete omsg;
}
