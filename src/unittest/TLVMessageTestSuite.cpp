/*
 * TLVMessageTestSuite.cpp
 *
 *  Created on: Mar 30, 2010
 *      Author: samael
 */

#include "TLVMessageTestSuite.h"
#include "TLVMessage.h"
#include "TLVMessageCreator.h"
#include "TLVBlock.h"
#include "CustomTLVTypes.h"
#include "TLVUInt32.h"
#include "TLVUInt16.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVMessageTestSuite);

using namespace cml;
using namespace wfe;

void TLVMessageTestSuite::testToTLVBlock()
{
	TLVMessage msg(TLVMessage::ADD_MASTER);
	TLVBlock *blk = msg.toTLVBlock();

	CPPUNIT_ASSERT_EQUAL((unsigned short)TLV_TYPE_MESSAGE, blk->type());
	CPPUNIT_ASSERT_EQUAL(TLVUInt16::Size, blk->length());

	delete blk;

	msg.setParameter(new TLVUInt32(2048));
	blk = msg.toTLVBlock();

	CPPUNIT_ASSERT_EQUAL((unsigned short)(TLVUInt16::Size + TLVUInt32::Size),
			blk->length());

	delete blk;
}
