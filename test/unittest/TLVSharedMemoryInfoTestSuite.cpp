/*
 * TLVSharedMemoryInfoTestSuite.cpp
 *
 *  Created on: Apr 8, 2010
 *      Author: samael
 */

#include <cstring>
#include "TLVSharedMemoryInfoTestSuite.h"
#include "TLVSharedMemoryInfo.h"
#include "CustomTLVTypes.h"
#include "TLVUInt32.h"
#include "TLVString.h"
#include "TLVBlock.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVSharedMemoryInfoTestSuite);

using namespace cml;
using namespace wfe;

void TLVSharedMemoryInfoTestSuite::testToTLVBlock()
{
	TLVSharedMemoryInfo info("this is a piece of shared memory", 16992);
	ITLVBlock *blk = info.toTLVBlock();

	CPPUNIT_ASSERT_EQUAL((unsigned short)TLV_TYPE_SMINFO, blk->type());
	CPPUNIT_ASSERT_EQUAL((unsigned short)(strlen("this is a piece of shared memory") +
			ITLVBlock::szHeader + TLVUInt32::Size), blk->length());

	SharedTLVBlock nameblk(blk->value());
	SharedTLVBlock sizeblk(blk->value() + nameblk.plainSize());
	CPPUNIT_ASSERT_EQUAL((unsigned short)TLV_TYPE_STRING, nameblk.type());
	CPPUNIT_ASSERT_EQUAL((unsigned short)TLV_TYPE_UINT32, sizeblk.type());

	delete blk;
}
