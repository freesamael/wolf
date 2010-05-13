/**
 * \file TLVUIntCreatorTestSuite.cpp
 * \date Apr 6, 2010
 * \author samael
 */

#include <TLVUInt16.h>
#include <TLVUInt16Creator.h>
#include <TLVUInt32.h>
#include <TLVUInt32Creator.h>
#include "TLVUIntCreatorTestSuite.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVUIntCreatorTestSuite);

using namespace cml;

void TLVUIntCreatorTestSuite::testUInt16()
{
	TLVUInt16 u16(5566);
	ITLVBlock *blk = u16.toTLVBlock();
	CPPUNIT_ASSERT_EQUAL((unsigned short)2, blk->length());

	TLVUInt16 *obj = dynamic_cast<TLVUInt16 *>(TLVUInt16Creator().create(*blk));
	CPPUNIT_ASSERT_EQUAL(u16.value(), obj->value());

	delete obj;
	delete blk;
}

void TLVUIntCreatorTestSuite::testUInt32()
{
	TLVUInt32 u32(7788);
	ITLVBlock *blk = u32.toTLVBlock();
	CPPUNIT_ASSERT_EQUAL((unsigned short)4, blk->length());

	TLVUInt32 *obj = dynamic_cast<TLVUInt32 *>(TLVUInt32Creator().create(*blk));
	CPPUNIT_ASSERT_EQUAL(u32.value(), obj->value());

	delete obj;
	delete blk;
}
