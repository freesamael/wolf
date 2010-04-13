/**
 * \file TLVMessageTestSuite.h
 * \date Mar 30, 2010
 * \author samael
 */

#ifndef TLVMESSAGETESTSUITE_H_
#define TLVMESSAGETESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TLVMessageTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TLVMessageTestSuite);
		CPPUNIT_TEST(testToTLVBlock);
	CPPUNIT_TEST_SUITE_END();

public:
	void testToTLVBlock();
};

#endif /* TLVMESSAGETESTSUITE_H_ */
