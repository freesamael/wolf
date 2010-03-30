/*
 * ProcessTestSuite.h
 *
 *  Created on: Mar 13, 2010
 *      Author: samael
 */

#ifndef PROCESSTESTSUITE_H_
#define PROCESSTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class ProcessTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(ProcessTestSuite);
		CPPUNIT_TEST(testConstructArgs);
	CPPUNIT_TEST_SUITE_END();

public:
	void testConstructArgs();
};

#endif /* PROCESSTESTSUITE_H_ */
