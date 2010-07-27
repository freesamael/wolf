/**
 * \file TLVCommandTestSuite.h
 * \date Mar 30, 2010
 * \author samael
 */

#ifndef TLVCOMMANDTESTSUITE_H_
#define TLVCOMMANDTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TLVCommandTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TLVCommandTestSuite);
		CPPUNIT_TEST(testToTLVBlock);
	CPPUNIT_TEST_SUITE_END();

public:
	void testToTLVBlock();
};

#endif /* TLVCOMMANDTESTSUITE_H_ */
