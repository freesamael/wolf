/*
 * TLVArrayTestSuite.cpp
 *
 *  Created on: Apr 8, 2010
 *      Author: samael
 */

#include "TLVArrayTestSuite.h"
#include "TLVArray.h"
#include "TLVUInt32.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVArrayTestSuite);

using namespace cml;

void TLVArrayTestSuite::testToTLVBlock()
{
	TLVArray array;
	TLVUInt32 u32s[10];
	for (int i = 0; i < 10; i++)
		array.elements().push_back(&u32s[i]);

	ITLVBlock *blk = array.toTLVBlock();
	CPPUNIT_ASSERT_EQUAL((unsigned short)80, blk->length());
	CPPUNIT_ASSERT_EQUAL((unsigned short)TLV_TYPE_ARRAY, blk->type());
	delete blk;
}
