/**
 * \file TLVBlockTestSuite.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include <vector>
#include <arpa/inet.h>
#include "TLVBlockTestSuite.h"
#include "CTlvBlock.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVBlockTestSuite);

using namespace cml;
using namespace std;

void TLVBlockTestSuite::testBlockOperations()
{
	CTlvBlock blk;
	blk.setType(0x55aa);
	blk.setLength(0x00ff);

	CPPUNIT_ASSERT_EQUAL((unsigned short)0x55aa, blk.type());
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x00ff, blk.length());
}

void TLVBlockTestSuite::testNestedBlocks()
{
	CTlvBlock b1(0x4321, 0x8), b2(0x1234, 0x8), b3(0xa5a5, 0x10);
	vector<const ITlvBlock *> v1;
	v1.push_back(&b1);
	v1.push_back(&b2);

	CTlvBlock *nb1 = CTlvBlock::concate(v1);
	vector<const ITlvBlock *> v2;
	v2.push_back(nb1);
	v2.push_back(&b3);

	CTlvBlock *nb2 = CTlvBlock::concate(v2);

	/*---------------------------------------nb2------------------------------------------------------
	 * |      |      | ----------------------nb1-------------------------------- --------b3--------- |
	 * |      |      | |      |      | --------b1--------- --------b2--------- | |      |      |   | |
	 * |0x0000|0x0030| |0x0000|0x0018| |0x4321|0x0008|...| |0x1234|0x0008|...| | |0xa5a5|0x0010|...| |
	 * |      |      | |      |      | ------------------- ------------------- | |      |      |   | |
	 * |      |      | --------------------------------------------------------- ------------------- |
	 * -----------------------------------------------------------------------------------------------
	 */

	CPPUNIT_ASSERT_EQUAL((unsigned short)0x0, nb2->type());
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x30, nb2->length());

	CPPUNIT_ASSERT_EQUAL((unsigned short)0x0, nb1->type());
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x18, nb1->length());
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x0, ntohs(((unsigned short *)nb2->value())[0]));
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x18, ntohs(((unsigned short *)nb2->value())[1]));

	CPPUNIT_ASSERT_EQUAL((unsigned short)0x4321, ntohs(((unsigned short *)nb1->value())[0]));
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x8, ntohs(((unsigned short *)nb1->value())[1]));

	CPPUNIT_ASSERT_EQUAL((unsigned short)0x1234, ntohs(((unsigned short *)(nb1->value() + b1.plainSize()))[0]));
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x8, ntohs(((unsigned short *)(nb1->value() + b1.plainSize()))[1]));

	CPPUNIT_ASSERT_EQUAL((unsigned short)0xa5a5, ntohs(((unsigned short *)(nb2->value() + nb1->plainSize()))[0]));
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x10, ntohs(((unsigned short *)(nb2->value() + nb1->plainSize()))[1]));

	delete nb1;
	delete nb2;
}
