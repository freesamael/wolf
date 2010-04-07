/*
 * TLVMessageCreatorTestSuite.h
 *
 *  Created on: Mar 30, 2010
 *      Author: samael
 */

#ifndef TLVMESSAGECREATORTESTSUITE_H_
#define TLVMESSAGECREATORTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TLVMessageCreatorTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TLVMessageCreatorTestSuite);
		CPPUNIT_TEST(testCreate);
	CPPUNIT_TEST_SUITE_END();

public:
	void testCreate();
};

#endif /* TLVMESSAGECREATORTESTSUITE_H_ */
