/**
 * \file TLVCommandCreatorTestSuite.h
 * \date Mar 30, 2010
 * \author samael
 */

#ifndef TLVCOMMANDCREATORTESTSUITE_H_
#define TLVCOMMANDCREATORTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TLVCommandCreatorTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TLVCommandCreatorTestSuite);
		CPPUNIT_TEST(testCreate);
	CPPUNIT_TEST_SUITE_END();

public:
	void testCreate();
};

#endif /* TLVCOMMANDCREATORTESTSUITE_H_ */
