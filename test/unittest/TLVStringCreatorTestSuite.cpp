/**
 * \file TLVStringCreatorTestSuite.cpp
 * \date Mar 11, 2010
 * \author samael
 */

#include "TLVStringCreatorTestSuite.h"
#include "CTlvStringCreator.h"
#include "CTlvString.h"
#include "CTlvBlock.h"

using namespace std;
using namespace wolf;

CPPUNIT_TEST_SUITE_REGISTRATION(TLVStringCreatorTestSuite);

void TLVStringCreatorTestSuite::testCreate()
{
	CTlvStringCreator *ctr = new CTlvStringCreator();
	CTlvString *str, *yastr;
	CTlvBlock *blk;

	str = dynamic_cast<CTlvString*>(ctr->create());
	str->setString("Hello World");
	CPPUNIT_ASSERT_EQUAL(string("Hello World"), str->toString());
	delete str;

	str = new CTlvString("Test TLVString/TLVBlock Conversion");
	blk = str->toTLVBlock();
	yastr = dynamic_cast<CTlvString*>(ctr->create(*blk));
	CPPUNIT_ASSERT_EQUAL(str->toString(), yastr->toString());
	delete yastr;
	delete blk;
	delete str;

	str = new CTlvString();
	blk = str->toTLVBlock();
	yastr = dynamic_cast<CTlvString*>(ctr->create(*blk));
	CPPUNIT_ASSERT_EQUAL(str->toString(), yastr->toString());
	delete yastr;
	delete blk;
	delete str;

	delete ctr;
}
