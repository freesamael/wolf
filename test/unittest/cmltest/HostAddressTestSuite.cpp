/**
 * \file HostAddressTestSuite.cpp
 * \date Apr 5, 2010
 * \author samael
 */

#include <string>
#include "HostAddressTestSuite.h"
#include "CHostAddress.h"

CPPUNIT_TEST_SUITE_REGISTRATION(HostAddressTestSuite);

using namespace std;
using namespace cml;

void HostAddressTestSuite::testToString()
{
	CHostAddress *addr;

	addr = new CHostAddress("127.0.0.1");
	CPPUNIT_ASSERT_EQUAL((string)"127.0.0.1", addr->toString());
	delete addr;

	addr = new CHostAddress("192.168.0.1");
	CPPUNIT_ASSERT_EQUAL((string)"192.168.0.1", addr->toString());
	delete addr;

	addr = new CHostAddress("255.255.255.255");
	CPPUNIT_ASSERT_EQUAL((string)"255.255.255.255", addr->toString());
	delete addr;
}
