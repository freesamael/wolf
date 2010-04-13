/**
 * \file TLVStringTestSuite.cpp
 * \date Mar 11, 2010
 * \author samael
 */

#include <cstring>
#include "TLVStringTestSuite.h"
#include "TLVStringCreator.h"
#include "TLVString.h"
#include "TLVBlock.h"

using namespace std;
using namespace cml;

CPPUNIT_TEST_SUITE_REGISTRATION(TLVStringTestSuite);

void TLVStringTestSuite::testToTLVBlock()
{
	TLVString *str;
	StandardTLVBlock *blk;

	str = new TLVString("12345");
	blk = str->toTLVBlock();
	CPPUNIT_ASSERT_EQUAL(TLV_TYPE_STRING, (int)blk->type());
	CPPUNIT_ASSERT_EQUAL(5, (int)blk->length());
	delete blk;
	delete str;

	str = new TLVString(string("Hello World"));
	blk = str->toTLVBlock();
	CPPUNIT_ASSERT_EQUAL(11, (int)blk->length());
	delete blk;
	delete str;
}
