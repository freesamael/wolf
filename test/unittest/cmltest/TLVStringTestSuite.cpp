/**
 * \file TLVStringTestSuite.cpp
 * \date Mar 11, 2010
 * \author samael
 */

#include <cstring>
#include "TLVStringTestSuite.h"
#include "CTlvStringCreator.h"
#include "CTlvString.h"
#include "CTlvBlock.h"

using namespace std;
using namespace wolf;

CPPUNIT_TEST_SUITE_REGISTRATION(TLVStringTestSuite);

void TLVStringTestSuite::testToTLVBlock()
{
	CTlvString *str;
	CTlvBlock *blk;

	str = new CTlvString("12345");
	blk = str->toTLVBlock();
	CPPUNIT_ASSERT_EQUAL(TLV_TYPE_STRING, (int)blk->type());
	CPPUNIT_ASSERT_EQUAL(5, (int)blk->length());
	delete blk;
	delete str;

	str = new CTlvString(string("Hello World"));
	blk = str->toTLVBlock();
	CPPUNIT_ASSERT_EQUAL(11, (int)blk->length());
	delete blk;
	delete str;
}
