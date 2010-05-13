/**
 * \file SinkPortTestSuite.h
 * \date Apr 13, 2010
 * \author samael
 */

#ifndef SINKPORTTESTSUITE_H_
#define SINKPORTTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class SinkPortTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(SinkPortTestSuite);
		CPPUNIT_TEST(testWriteReadPort);
	CPPUNIT_TEST_SUITE_END();

public:
	void testWriteReadPort();
};

#endif /* SINKPORTTESTSUITE_H_ */
