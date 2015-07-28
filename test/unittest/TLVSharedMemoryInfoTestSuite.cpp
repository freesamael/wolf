/**
 * \file TLVSharedMemoryInfoTestSuite.cpp
 * \date Apr 8, 2010
 * \author samael
 */

#include <cstring>
#include "TLVSharedMemoryInfoTestSuite.h"
#include "CTlvSharedMemoryInfo.h"
#include "CmlTLVTypes.h"
#include "CTlvUint32.h"
#include "CTlvString.h"
#include "CTlvBlock.h"
#include "WfeTLVTypes.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVSharedMemoryInfoTestSuite);

using namespace wolf;
using namespace wolf;

void TLVSharedMemoryInfoTestSuite::testToTLVBlock()
{
	CTlvSharedMemoryInfo info("this is a piece of shared memory", 16992);
	ITlvBlock *blk = info.toTLVBlock();

	CPPUNIT_ASSERT_EQUAL((uint32_t)TLV_TYPE_SMINFO, blk->type());
	CPPUNIT_ASSERT_EQUAL((uint32_t)(strlen("this is a piece of shared memory") +
			ITlvBlock::szHeader + CTlvUint32::Size), blk->length());

	CSharedTlvBlock nameblk(blk->value());
	CSharedTlvBlock sizeblk(blk->value() + nameblk.plainSize());
	CPPUNIT_ASSERT_EQUAL((uint32_t)TLV_TYPE_STRING, nameblk.type());
	CPPUNIT_ASSERT_EQUAL((uint32_t)TLV_TYPE_UINT32, sizeblk.type());

	delete blk;
}
