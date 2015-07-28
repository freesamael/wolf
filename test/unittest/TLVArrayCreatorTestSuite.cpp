/**
 * \file TLVArrayCreatorTestSuite.cpp
 * \date Apr 8, 2010
 * \author samael
 */

#include <string>
#include "TLVArrayCreatorTestSuite.h"
#include "CTlvArray.h"
#include "CTlvArrayCreator.h"
#include "CTlvUint32.h"
#include "CTlvUint16.h"
#include "CTlvString.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVArrayCreatorTestSuite);

using namespace std;
using namespace wolf;

void TLVArrayCreatorTestSuite::testCreate()
{
	CTlvArray array;

	ITlvBlock *blk = array.toTLVBlock();
	CTlvArray *oary = (CTlvArray *)CTlvArrayCreator().create(*blk);
	CPPUNIT_ASSERT_EQUAL((size_t)0, oary->elements().size());
	delete blk;
	delete oary;

	CTlvUint32 u32(19950101);
	CTlvUint16 u16(8877);
	CTlvString str("Hello -u Potin -c \"Oh oh android ohohoh\"");
	array.elements().push_back(&u32);
	array.elements().push_back(&u16);
	array.elements().push_back(&str);
	blk = array.toTLVBlock();

	oary = (CTlvArray *)CTlvArrayCreator().create(*blk);
	CPPUNIT_ASSERT_EQUAL((size_t)3, oary->elements().size());

	CTlvUint32 *ou32 = (CTlvUint32 *)oary->elements()[0];
	CTlvUint16 *ou16 = (CTlvUint16 *)oary->elements()[1];
	CTlvString *ostr = (CTlvString *)oary->elements()[2];
	CPPUNIT_ASSERT_EQUAL((uint32_t)19950101, ou32->value());
	CPPUNIT_ASSERT_EQUAL((uint32_t)8877, ou16->value());
	CPPUNIT_ASSERT_EQUAL((string)"Hello -u Potin -c \"Oh oh android ohohoh\"", ostr->toString());

	delete blk;
	delete oary;
	delete ou32;
	delete ou16;
	delete ostr;
}
