/**
 * \file TLVUIntCreatorTestSuite.cpp
 * \date Apr 6, 2010
 * \author samael
 */

#include <CTlvUint16.h>
#include <CTlvUint16Creator.h>
#include <CTlvUint32.h>
#include <CTlvUint32Creator.h>
#include "TLVUIntCreatorTestSuite.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVUIntCreatorTestSuite);

using namespace cml;

void TLVUIntCreatorTestSuite::testUInt16()
{
	CTlvUint16 u16(5566);
	ITlvBlock *blk = u16.toTLVBlock();
	CPPUNIT_ASSERT_EQUAL((unsigned short)2, blk->length());

	CTlvUint16 *obj = dynamic_cast<CTlvUint16 *>(CTlvUint16Creator().create(*blk));
	CPPUNIT_ASSERT_EQUAL(u16.value(), obj->value());

	delete obj;
	delete blk;
}

void TLVUIntCreatorTestSuite::testUInt32()
{
	CTlvUint32 u32(7788);
	ITlvBlock *blk = u32.toTLVBlock();
	CPPUNIT_ASSERT_EQUAL((unsigned short)4, blk->length());

	CTlvUint32 *obj = dynamic_cast<CTlvUint32 *>(CTlvUint32Creator().create(*blk));
	CPPUNIT_ASSERT_EQUAL(u32.value(), obj->value());

	delete obj;
	delete blk;
}
