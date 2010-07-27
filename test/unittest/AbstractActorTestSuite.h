/**
 * \file AbstractActorTestSuite.h
 * \date Jun 21, 2010
 * \author samael
 */

#ifndef ABSTRACTACTORTESTSUITE_H_
#define ABSTRACTACTORTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class AbstractActorTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(AbstractActorTestSuite);
		CPPUNIT_TEST(testAddRemovePort);
	CPPUNIT_TEST_SUITE_END();

public:
	void testAddRemovePort();
};

#endif /* ABSTRACTACTORTESTSUITE_H_ */
