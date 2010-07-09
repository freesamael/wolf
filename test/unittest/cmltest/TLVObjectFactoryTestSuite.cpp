/**
 * \file TLVObjectFactoryTestSuite.cpp
 * \date Apr 6, 2010
 * \author samael
 */

#include <string>
#include <CTlvObjectFactory.h>
#include <CTlvUint16.h>
#include <CTlvUint32.h>
#include <CTlvString.h>
#include <CTlvCommand.h>
#include <CmlTLVTypes.h>
#include <CTlvBlock.h>
#include <WfeTLVTypes.h>
#include "TLVObjectFactoryTestSuite.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVObjectFactoryTestSuite);

using namespace std;
using namespace cml;
using namespace wfe;

void TLVObjectFactoryTestSuite::testLookupName()
{
	CPPUNIT_ASSERT_EQUAL((string)typeid(CTlvUint16).name(),
			(string)CTlvObjectFactory::instance()->lookupTypeName(TLV_TYPE_UINT16));
	CPPUNIT_ASSERT_EQUAL((string)typeid(CTlvUint32).name(),
			(string)CTlvObjectFactory::instance()->lookupTypeName(TLV_TYPE_UINT32));
	CPPUNIT_ASSERT_EQUAL((string)typeid(CTlvString).name(),
			(string)CTlvObjectFactory::instance()->lookupTypeName(TLV_TYPE_STRING));
	CPPUNIT_ASSERT_EQUAL((string)typeid(CTlvCommand).name(),
			(string)CTlvObjectFactory::instance()->lookupTypeName(TLV_TYPE_COMMAND_BASE));
}

void TLVObjectFactoryTestSuite::testCreateById()
{
	ITlvObject *obj = CTlvObjectFactory::instance()->createTLVObject(TLV_TYPE_UINT16);
	CPPUNIT_ASSERT_EQUAL(typeid(CTlvUint16).name(), typeid(*obj).name());
	delete obj;

	obj = CTlvObjectFactory::instance()->createTLVObject(TLV_TYPE_UINT32);
	CPPUNIT_ASSERT_EQUAL(typeid(CTlvUint32).name(), typeid(*obj).name());
	delete obj;

	obj = CTlvObjectFactory::instance()->createTLVObject(TLV_TYPE_STRING);
	CPPUNIT_ASSERT_EQUAL(typeid(CTlvString).name(), typeid(*obj).name());
	delete obj;

	obj = CTlvObjectFactory::instance()->createTLVObject(TLV_TYPE_COMMAND_BASE);
	CPPUNIT_ASSERT_EQUAL(typeid(CTlvCommand).name(), typeid(*obj).name());
	delete obj;
}

void TLVObjectFactoryTestSuite::testCreateByName()
{
	ITlvObject *obj = CTlvObjectFactory::instance()->createTLVObject(typeid(CTlvUint16).name());
	CPPUNIT_ASSERT_EQUAL(typeid(CTlvUint16).name(), typeid(*obj).name());
	delete obj;

	obj = CTlvObjectFactory::instance()->createTLVObject(typeid(CTlvUint32).name());
	CPPUNIT_ASSERT_EQUAL(typeid(CTlvUint32).name(), typeid(*obj).name());
	delete obj;

	obj = CTlvObjectFactory::instance()->createTLVObject(typeid(CTlvString).name());
	CPPUNIT_ASSERT_EQUAL(typeid(CTlvString).name(), typeid(*obj).name());
	delete obj;

	obj = CTlvObjectFactory::instance()->createTLVObject(typeid(CTlvCommand).name());
	CPPUNIT_ASSERT_EQUAL(typeid(CTlvCommand).name(), typeid(*obj).name());
	delete obj;
}

void TLVObjectFactoryTestSuite::testCreateByTLVBlock()
{
	ITlvBlock *blk = CTlvUint16().toTLVBlock();
	ITlvObject *obj = CTlvObjectFactory::instance()->createTLVObject(*blk);
	CPPUNIT_ASSERT_EQUAL(typeid(CTlvUint16).name(), typeid(*obj).name());
	delete obj;
	delete blk;

	blk = CTlvUint32().toTLVBlock();
	obj = CTlvObjectFactory::instance()->createTLVObject(*blk);
	CPPUNIT_ASSERT_EQUAL(typeid(CTlvUint32).name(), typeid(*obj).name());
	delete obj;
	delete blk;

	blk = CTlvString().toTLVBlock();
	obj = CTlvObjectFactory::instance()->createTLVObject(*blk);
	CPPUNIT_ASSERT_EQUAL(typeid(CTlvString).name(), typeid(*obj).name());
	delete obj;
	delete blk;

	blk = CTlvCommand().toTLVBlock();
	obj = CTlvObjectFactory::instance()->createTLVObject(*blk);
	CPPUNIT_ASSERT_EQUAL(typeid(CTlvCommand).name(), typeid(*obj).name());
	delete obj;
	delete blk;
}
