/*
 * TLVSharedMemoryInfoTestSuite.h
 *
 *  Created on: Apr 8, 2010
 *      Author: samael
 */

#ifndef TLVSHAREDMEMORYINFOTESTSUITE_H_
#define TLVSHAREDMEMORYINFOTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TLVSharedMemoryInfoTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TLVSharedMemoryInfoTestSuite);
		CPPUNIT_TEST(testToTLVBlock);
	CPPUNIT_TEST_SUITE_END();

public:
	void testToTLVBlock();
};

#endif /* TLVSHAREDMEMORYINFOTESTSUITE_H_ */
