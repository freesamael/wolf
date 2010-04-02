/*
 * TLVBlockTestSuite.cpp
 *
 *  Created on: Mar 30, 2010
 *      Author: samael
 */

#include <vector>
#include <arpa/inet.h>
#include "TLVBlockTestSuite.h"
#include "TLVBlock.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVBlockTestSuite);

using namespace cml;
using namespace std;

void TLVBlockTestSuite::testBlockOperations()
{
	StandardTLVBlock blk;
	blk.setType(0x55aa);
	blk.setLength(0x00ff);

	CPPUNIT_ASSERT_EQUAL((unsigned short)0x55aa, blk.type());
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x00ff, blk.length());
}

void TLVBlockTestSuite::testNestedBlocks()
{
	StandardTLVBlock b1(0x4321, 0x8), b2(0x1234, 0x8), b3(0xa5a5, 0x10);
	vector<const ITLVBlock *> v1;
	v1.push_back(&b1);
	v1.push_back(&b2);

	StandardTLVBlock *nb1 = StandardTLVBlock::concate(v1);
	vector<const ITLVBlock *> v2;
	v2.push_back(nb1);
	v2.push_back(&b3);

	StandardTLVBlock *nb2 = StandardTLVBlock::concate(v2);

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
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x0, ntohs(((unsigned short *)nb2->getValueBuffer())[0]));
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x18, ntohs(((unsigned short *)nb2->getValueBuffer())[1]));

	CPPUNIT_ASSERT_EQUAL((unsigned short)0x4321, ntohs(((unsigned short *)nb1->getValueBuffer())[0]));
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x8, ntohs(((unsigned short *)nb1->getValueBuffer())[1]));

	CPPUNIT_ASSERT_EQUAL((unsigned short)0x1234, ntohs(((unsigned short *)(nb1->getValueBuffer() + b1.size()))[0]));
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x8, ntohs(((unsigned short *)(nb1->getValueBuffer() + b1.size()))[1]));

	CPPUNIT_ASSERT_EQUAL((unsigned short)0xa5a5, ntohs(((unsigned short *)(nb2->getValueBuffer() + nb1->size()))[0]));
	CPPUNIT_ASSERT_EQUAL((unsigned short)0x10, ntohs(((unsigned short *)(nb2->getValueBuffer() + nb1->size()))[1]));

	delete nb1;
	delete nb2;
}
