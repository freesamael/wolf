/*
 * UDPSocketTestSuite.h
 *
 *  Created on: Apr 6, 2010
 *      Author: samael
 */

#ifndef UDPSOCKETTESTSUITE_H_
#define UDPSOCKETTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class UDPSocketTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(UDPSocketTestSuite);
		CPPUNIT_TEST(testSendtoRecvfrom);
		CPPUNIT_TEST(testReadWrite);
	CPPUNIT_TEST_SUITE_END();

public:
	void testSendtoRecvfrom();
	void testReadWrite();
};

#endif /* UDPSOCKETTESTSUITE_H_ */
