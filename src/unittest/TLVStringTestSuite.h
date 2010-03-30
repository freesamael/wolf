/*
 * TLVStringTestSuite.h
 *
 *  Created on: Mar 11, 2010
 *      Author: samael
 */

#ifndef TLVSTRINGTESTSUITE_H_
#define TLVSTRINGTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TLVStringTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TLVStringTestSuite);
		CPPUNIT_TEST(testToTLVBlock);
	CPPUNIT_TEST_SUITE_END();
public:
	void testToTLVBlock();
};

#endif /* TLVSTRINGTESTSUITE_H_ */
