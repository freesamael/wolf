/**
 * \file TLVObjectFactoryTestSuite.cpp
 * \date Apr 6, 2010
 * \author samael
 */

#include <typeinfo>
#include <string>
#include <CTlvObjectFactory.h>
#include <CTlvUint16.h>
#include <CTlvUint32.h>
#include <CTlvString.h>
#include <CTlvCommand.h>
#include <CmlTLVTypes.h>
#include <CTlvBlock.h>
#include <WfeTLVTypes.h>
#include <HelperMacros.h>
#include "TLVObjectFactoryTestSuite.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVObjectFactoryTestSuite);

using namespace std;
using namespace wolf;
using namespace wolf;

void TLVObjectFactoryTestSuite::testLookupName()
{
	CPPUNIT_ASSERT_EQUAL((string)TYPENAME(CTlvUint16),
			(string)CTlvObjectFactory::instance()->lookupTypeName(TLV_TYPE_UINT16));
	CPPUNIT_ASSERT_EQUAL((string)TYPENAME(CTlvUint32),
			(string)CTlvObjectFactory::instance()->lookupTypeName(TLV_TYPE_UINT32));
	CPPUNIT_ASSERT_EQUAL((string)TYPENAME(CTlvString),
			(string)CTlvObjectFactory::instance()->lookupTypeName(TLV_TYPE_STRING));
	CPPUNIT_ASSERT_EQUAL((string)TYPENAME(CTlvCommand),
			(string)CTlvObjectFactory::instance()->lookupTypeName(TLV_TYPE_COMMAND_BASE));
}

void TLVObjectFactoryTestSuite::testCreateById()
{
	ITlvObject *obj = CTlvObjectFactory::instance()->createTLVObject(TLV_TYPE_UINT16);
	CPPUNIT_ASSERT_EQUAL(TYPENAME(CTlvUint16), TYPENAME(*obj));
	delete obj;

	obj = CTlvObjectFactory::instance()->createTLVObject(TLV_TYPE_UINT32);
	CPPUNIT_ASSERT_EQUAL(TYPENAME(CTlvUint32), TYPENAME(*obj));
	delete obj;

	obj = CTlvObjectFactory::instance()->createTLVObject(TLV_TYPE_STRING);
	CPPUNIT_ASSERT_EQUAL(TYPENAME(CTlvString), TYPENAME(*obj));
	delete obj;

	obj = CTlvObjectFactory::instance()->createTLVObject(TLV_TYPE_COMMAND_BASE);
	CPPUNIT_ASSERT_EQUAL(TYPENAME(CTlvCommand), TYPENAME(*obj));
	delete obj;
}

void TLVObjectFactoryTestSuite::testCreateByName()
{
	ITlvObject *obj = CTlvObjectFactory::instance()->createTLVObject(TYPENAME(CTlvUint16));
	CPPUNIT_ASSERT_EQUAL(TYPENAME(CTlvUint16), TYPENAME(*obj));
	delete obj;

	obj = CTlvObjectFactory::instance()->createTLVObject(TYPENAME(CTlvUint32));
	CPPUNIT_ASSERT_EQUAL(TYPENAME(CTlvUint32), TYPENAME(*obj));
	delete obj;

	obj = CTlvObjectFactory::instance()->createTLVObject(TYPENAME(CTlvString));
	CPPUNIT_ASSERT_EQUAL(TYPENAME(CTlvString), TYPENAME(*obj));
	delete obj;

	obj = CTlvObjectFactory::instance()->createTLVObject(TYPENAME(CTlvCommand));
	CPPUNIT_ASSERT_EQUAL(TYPENAME(CTlvCommand), TYPENAME(*obj));
	delete obj;
}

void TLVObjectFactoryTestSuite::testCreateByTLVBlock()
{
	ITlvBlock *blk = CTlvUint16().toTLVBlock();
	ITlvObject *obj = CTlvObjectFactory::instance()->createTLVObject(*blk);
	CPPUNIT_ASSERT_EQUAL(TYPENAME(CTlvUint16), TYPENAME(*obj));
	delete obj;
	delete blk;

	blk = CTlvUint32().toTLVBlock();
	obj = CTlvObjectFactory::instance()->createTLVObject(*blk);
	CPPUNIT_ASSERT_EQUAL(TYPENAME(CTlvUint32), TYPENAME(*obj));
	delete obj;
	delete blk;

	blk = CTlvString().toTLVBlock();
	obj = CTlvObjectFactory::instance()->createTLVObject(*blk);
	CPPUNIT_ASSERT_EQUAL(TYPENAME(CTlvString), TYPENAME(*obj));
	delete obj;
	delete blk;

	blk = CTlvCommand().toTLVBlock();
	obj = CTlvObjectFactory::instance()->createTLVObject(*blk);
	CPPUNIT_ASSERT_EQUAL(TYPENAME(CTlvCommand), TYPENAME(*obj));
	delete obj;
	delete blk;
}
