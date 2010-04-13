/**
 * \file TLVArrayTestSuite.h
 * \date Apr 8, 2010
 * \author samael
 */

#ifndef TLVARRAYTESTSUITE_H_
#define TLVARRAYTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TLVArrayTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TLVArrayTestSuite);
		CPPUNIT_TEST(testToTLVBlock);
	CPPUNIT_TEST_SUITE_END();

public:
	void testToTLVBlock();
};

#endif /* TLVARRAYTESTSUITE_H_ */
