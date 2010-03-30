/*
 * ProcessEnvironmentTestSuite.h
 *
 *  Created on: Mar 13, 2010
 *      Author: samael
 */

#ifndef PROCESSENVIRONMENTTESTSUITE_H_
#define PROCESSENVIRONMENTTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class ProcessEnvironmentTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(ProcessEnvironmentTestSuite);
		CPPUNIT_TEST(testSystemEnvironment);
		CPPUNIT_TEST(testSetClearVariable);
	CPPUNIT_TEST_SUITE_END();

public:
	void testSystemEnvironment();
	void testSetClearVariable();
};

#endif /* PROCESSENVIRONMENTTESTSUITE_H_ */
