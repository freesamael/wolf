/**
 * \file TLVArrayCreatorTestSuite.cpp
 * \date Apr 8, 2010
 * \author samael
 */

#include <string>
#include "TLVArrayCreatorTestSuite.h"
#include "TLVArray.h"
#include "TLVArrayCreator.h"
#include "TLVUInt32.h"
#include "TLVUInt16.h"
#include "TLVString.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVArrayCreatorTestSuite);

using namespace std;
using namespace cml;

void TLVArrayCreatorTestSuite::testCreate()
{
	TLVArray array;

	ITLVBlock *blk = array.toTLVBlock();
	TLVArray *oary = (TLVArray *)TLVArrayCreator().create(*blk);
	CPPUNIT_ASSERT_EQUAL((unsigned)0, oary->elements().size());
	delete blk;
	delete oary;

	TLVUInt32 u32(19950101);
	TLVUInt16 u16(8877);
	TLVString str("Hello -u Potin -c \"Oh oh android ohohoh\"");
	array.elements().push_back(&u32);
	array.elements().push_back(&u16);
	array.elements().push_back(&str);
	blk = array.toTLVBlock();

	oary = (TLVArray *)TLVArrayCreator().create(*blk);
	CPPUNIT_ASSERT_EQUAL((unsigned)3, oary->elements().size());

	TLVUInt32 *ou32 = (TLVUInt32 *)oary->elements()[0];
	TLVUInt16 *ou16 = (TLVUInt16 *)oary->elements()[1];
	TLVString *ostr = (TLVString *)oary->elements()[2];
	CPPUNIT_ASSERT_EQUAL((unsigned)19950101, ou32->value());
	CPPUNIT_ASSERT_EQUAL((unsigned short)8877, ou16->value());
	CPPUNIT_ASSERT_EQUAL((string)"Hello -u Potin -c \"Oh oh android ohohoh\"", ostr->toString());

	delete blk;
	delete oary;
	delete ou32;
	delete ou16;
	delete ostr;
}
