/**
 * \file TLVSharedMemoryInfoCreatorTestSuite.cpp
 * \date Apr 8, 2010
 * \author samael
 */

#include "TLVSharedMemoryInfoCreatorTestSuite.h"
#include "TLVSharedMemoryInfoCreator.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVSharedMemoryInfoCreatorTestSuite);

using namespace cml;
using namespace wfe;

void TLVSharedMemoryInfoCreatorTestSuite::testCreate()
{
	TLVSharedMemoryInfo i1("test", 123), i2("hello", 456),
			i3("name of shared memory", 7788), i4("7-11", 5566),
			i5("The answer of life, the universe and everything", 42);
	ITLVBlock *b1 = i1.toTLVBlock(), *b2 = i2.toTLVBlock(),
			*b3 = i3.toTLVBlock(), *b4 = i4.toTLVBlock(), *b5 = i5.toTLVBlock();
	TLVSharedMemoryInfoCreator c;
	TLVSharedMemoryInfo *o1 = (TLVSharedMemoryInfo *)c.create(*b1),
			*o2 = (TLVSharedMemoryInfo *)c.create(*b2),
			*o3 = (TLVSharedMemoryInfo *)c.create(*b3),
			*o4 = (TLVSharedMemoryInfo *)c.create(*b4),
			*o5 = (TLVSharedMemoryInfo *)c.create(*b5);

	CPPUNIT_ASSERT_EQUAL(i1.name(), o1->name());
	CPPUNIT_ASSERT_EQUAL(i1.size(), o1->size());
	CPPUNIT_ASSERT_EQUAL(i2.name(), o2->name());
	CPPUNIT_ASSERT_EQUAL(i2.size(), o2->size());
	CPPUNIT_ASSERT_EQUAL(i3.name(), o3->name());
	CPPUNIT_ASSERT_EQUAL(i3.size(), o3->size());
	CPPUNIT_ASSERT_EQUAL(i4.name(), o4->name());
	CPPUNIT_ASSERT_EQUAL(i4.size(), o4->size());
	CPPUNIT_ASSERT_EQUAL(i5.name(), o5->name());
	CPPUNIT_ASSERT_EQUAL(i5.size(), o5->size());

	delete b1;
	delete b2;
	delete b3;
	delete b4;
	delete b5;
	delete o1;
	delete o2;
	delete o3;
	delete o4;
	delete o5;
}
