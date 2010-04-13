/**
 * \file TLVStringCreatorTestSuite.cpp
 * \date Mar 11, 2010
 * \author samael
 */

#include "TLVStringCreatorTestSuite.h"
#include "TLVStringCreator.h"
#include "TLVString.h"
#include "TLVBlock.h"

using namespace std;
using namespace cml;

CPPUNIT_TEST_SUITE_REGISTRATION(TLVStringCreatorTestSuite);

void TLVStringCreatorTestSuite::testCreate()
{
	TLVStringCreator *ctr = new TLVStringCreator();
	TLVString *str, *yastr;
	StandardTLVBlock *blk;

	str = dynamic_cast<TLVString*>(ctr->create());
	str->setString("Hello World");
	CPPUNIT_ASSERT_EQUAL(string("Hello World"), str->toString());
	delete str;

	str = new TLVString("Test TLVString/TLVBlock Conversion");
	blk = str->toTLVBlock();
	yastr = dynamic_cast<TLVString*>(ctr->create(*blk));
	CPPUNIT_ASSERT_EQUAL(str->toString(), yastr->toString());
	delete yastr;
	delete blk;
	delete str;

	str = new TLVString();
	blk = str->toTLVBlock();
	yastr = dynamic_cast<TLVString*>(ctr->create(*blk));
	CPPUNIT_ASSERT_EQUAL(str->toString(), yastr->toString());
	delete yastr;
	delete blk;
	delete str;

	delete ctr;
}
