/*
 * TLVUIntCreatorTestSuite.h
 *
 *  Created on: Apr 6, 2010
 *      Author: samael
 */

#ifndef TLVUINTCREATORTESTSUITE_H_
#define TLVUINTCREATORTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TLVUIntCreatorTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TLVUIntCreatorTestSuite);
		CPPUNIT_TEST(testUInt16);
		CPPUNIT_TEST(testUInt32);
	CPPUNIT_TEST_SUITE_END();

public:
	void testUInt16();
	void testUInt32();
};

#endif /* TLVUINTCREATORTESTSUITE_H_ */
