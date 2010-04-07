/*
 * TLVStringCreatorTestSuite.h
 *
 *  Created on: Mar 11, 2010
 *      Author: samael
 */

#ifndef TLVSTRINGCREATORTESTSUITE_H_
#define TLVSTRINGCREATORTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TLVStringCreatorTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TLVStringCreatorTestSuite);
		CPPUNIT_TEST(testCreate);
	CPPUNIT_TEST_SUITE_END();

public:
	void testCreate();
};

#endif /* TLVSTRINGCREATORTESTSUITE_H_ */
