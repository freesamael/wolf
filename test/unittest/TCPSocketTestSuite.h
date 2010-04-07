/*
 * TCPSocketTestSuite.h
 *
 *  Created on: Apr 6, 2010
 *      Author: samael
 */

#ifndef TCPSOCKETTESTSUITE_H_
#define TCPSOCKETTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TCPSocketTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TCPSocketTestSuite);
		CPPUNIT_TEST(testReadWrite);
	CPPUNIT_TEST_SUITE_END();

public:
	void testReadWrite();
};

#endif /* TCPSOCKETTESTSUITE_H_ */
