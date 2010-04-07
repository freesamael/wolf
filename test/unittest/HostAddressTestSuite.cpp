/*
 * HostAddressTestSuite.cpp
 *
 *  Created on: Apr 5, 2010
 *      Author: samael
 */

#include <string>
#include "HostAddressTestSuite.h"
#include "HostAddress.h"

CPPUNIT_TEST_SUITE_REGISTRATION(HostAddressTestSuite);

using namespace std;
using namespace cml;

void HostAddressTestSuite::testToString()
{
	HostAddress *addr;

	addr = new HostAddress("127.0.0.1");
	CPPUNIT_ASSERT_EQUAL((string)"127.0.0.1", addr->toString());
	delete addr;

	addr = new HostAddress("192.168.0.1");
	CPPUNIT_ASSERT_EQUAL((string)"192.168.0.1", addr->toString());
	delete addr;

	addr = new HostAddress("255.255.255.255");
	CPPUNIT_ASSERT_EQUAL((string)"255.255.255.255", addr->toString());
	delete addr;
}
