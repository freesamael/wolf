/**
 * \file TLVSharedMemoryInfoCreatorTestSuite.h
 * \date Apr 8, 2010
 * \author samael
 */

#ifndef TLVSHAREDMEMORYINFOCREATORTESTSUITE_H_
#define TLVSHAREDMEMORYINFOCREATORTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TLVSharedMemoryInfoCreatorTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TLVSharedMemoryInfoCreatorTestSuite);
		CPPUNIT_TEST(testCreate);
	CPPUNIT_TEST_SUITE_END();

public:
	void testCreate();
};

#endif /* TLVSHAREDMEMORYINFOCREATORTESTSUITE_H_ */
