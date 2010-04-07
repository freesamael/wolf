/*
 * HostAddressTestSuite.h
 *
 *  Created on: Apr 5, 2010
 *      Author: samael
 */

#ifndef HOSTADDRESSTESTSUITE_H_
#define HOSTADDRESSTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class HostAddressTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(HostAddressTestSuite);
		CPPUNIT_TEST(testToString);
	CPPUNIT_TEST_SUITE_END();

public:
	void testToString();
};

#endif /* HOSTADDRESSTESTSUITE_H_ */
