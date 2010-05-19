/**
 * \file TLVObjectFactoryTestSuite.h
 * \date Apr 6, 2010
 * \author samael
 */

#ifndef TLVOBJECTFACTORYTESTSUITE_H_
#define TLVOBJECTFACTORYTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TLVObjectFactoryTestSuite: public TestCase
{
	CPPUNIT_TEST_SUITE(TLVObjectFactoryTestSuite);
		CPPUNIT_TEST(testLookupName);
		CPPUNIT_TEST(testCreateById);
		CPPUNIT_TEST(testCreateByName);
		CPPUNIT_TEST(testCreateByTLVBlock);
	CPPUNIT_TEST_SUITE_END();

public:
	void testLookupName();
	void testCreateById();
	void testCreateByName();
	void testCreateByTLVBlock();
};

#endif /* TLVOBJECTFACTORYTESTSUITE_H_ */
