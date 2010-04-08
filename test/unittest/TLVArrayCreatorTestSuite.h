/*
 * TLVArrayCreatorTestSuite.h
 *
 *  Created on: Apr 8, 2010
 *      Author: samael
 */

#ifndef TLVARRAYCREATORTESTSUITE_H_
#define TLVARRAYCREATORTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TLVArrayCreatorTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TLVArrayCreatorTestSuite);
		CPPUNIT_TEST(testCreate);
	CPPUNIT_TEST_SUITE_END();

public:
	void testCreate();
};

#endif /* TLVARRAYCREATORTESTSUITE_H_ */
