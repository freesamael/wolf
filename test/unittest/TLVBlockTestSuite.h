/**
 * \file TLVBlockTestSuite.h
 * \date Mar 30, 2010
 * \author samael
 */

#ifndef TLVBLOCKTESTSUITE_H_
#define TLVBLOCKTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TLVBlockTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TLVBlockTestSuite);
		CPPUNIT_TEST(testBlockOperations);
		CPPUNIT_TEST(testNestedBlocks);
	CPPUNIT_TEST_SUITE_END();

public:
	void testBlockOperations();
	void testNestedBlocks();
};

#endif /* TLVBLOCKTESTSUITE_H_ */
