/*
 * StringHelperTestSuite.h
 *
 *  Created on: Mar 6, 2010
 *      Author: samael
 */

#ifndef STRINGHELPERTESTSUITE_H_
#define STRINGHELPERTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class StringHelperTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(StringHelperTestSuite);
		CPPUNIT_TEST(testTokenSingleCharDelim);
		CPPUNIT_TEST(testTokenMultCharDelim);
		CPPUNIT_TEST(testTokenWithOldData);
	CPPUNIT_TEST_SUITE_END();
public:
	void testTokenSingleCharDelim();
	void testTokenMultCharDelim();
	void testTokenWithOldData();
};

#endif /* STRINGHELPERTESTSUITE_H_ */
