/**
 * \file ChannelTestSuite.h
 * \date Apr 13, 2010
 * \author samael
 */

#ifndef CHANNELTESTSUITE_H_
#define CHANNELTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class ChannelTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(ChannelTestSuite);
		CPPUNIT_TEST(testAttachDetach);
		CPPUNIT_TEST(testWrite);
	CPPUNIT_TEST_SUITE_END();

public:
	void testAttachDetach();
	void testWrite();
};

#endif /* CHANNELTESTSUITE_H_ */
