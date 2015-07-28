/**
 * \file TLVArrayTestSuite.cpp
 * \date Apr 8, 2010
 * \author samael
 */

#include "TLVArrayTestSuite.h"
#include "CTlvArray.h"
#include "CTlvUint32.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVArrayTestSuite);

using namespace wolf;

void TLVArrayTestSuite::testToTLVBlock()
{
	CTlvArray array;
	CTlvUint32 u32s[10];
	for (int i = 0; i < 10; i++)
		array.elements().push_back(&u32s[i]);

	ITlvBlock *blk = array.toTLVBlock();
	CPPUNIT_ASSERT_EQUAL((uint32_t)120, blk->length());
	CPPUNIT_ASSERT_EQUAL((uint32_t)TLV_TYPE_ARRAY, blk->type());
	delete blk;
}
