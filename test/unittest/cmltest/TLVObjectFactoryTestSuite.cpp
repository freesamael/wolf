/**
 * \file TLVObjectFactoryTestSuite.cpp
 * \date Apr 6, 2010
 * \author samael
 */

#include <string>
#include <TLVObjectFactory.h>
#include <TLVUInt16.h>
#include <TLVUInt32.h>
#include <TLVString.h>
#include <TLVCommand.h>
#include <CmlTLVTypes.h>
#include <TLVBlock.h>
#include <WfeTLVTypes.h>
#include "TLVObjectFactoryTestSuite.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVObjectFactoryTestSuite);

using namespace std;
using namespace cml;
using namespace wfe;

void TLVObjectFactoryTestSuite::testLookupName()
{
	CPPUNIT_ASSERT_EQUAL((string)typeid(TLVUInt16).name(),
			(string)TLVObjectFactory::instance()->lookupTypeName(TLV_TYPE_UINT16));
	CPPUNIT_ASSERT_EQUAL((string)typeid(TLVUInt32).name(),
			(string)TLVObjectFactory::instance()->lookupTypeName(TLV_TYPE_UINT32));
	CPPUNIT_ASSERT_EQUAL((string)typeid(TLVString).name(),
			(string)TLVObjectFactory::instance()->lookupTypeName(TLV_TYPE_STRING));
	CPPUNIT_ASSERT_EQUAL((string)typeid(TLVCommand).name(),
			(string)TLVObjectFactory::instance()->lookupTypeName(TLV_TYPE_COMMAND_BASE));
}

void TLVObjectFactoryTestSuite::testCreateById()
{
	ITLVObject *obj = TLVObjectFactory::instance()->createTLVObject(TLV_TYPE_UINT16);
	CPPUNIT_ASSERT_EQUAL(typeid(TLVUInt16).name(), typeid(*obj).name());
	delete obj;

	obj = TLVObjectFactory::instance()->createTLVObject(TLV_TYPE_UINT32);
	CPPUNIT_ASSERT_EQUAL(typeid(TLVUInt32).name(), typeid(*obj).name());
	delete obj;

	obj = TLVObjectFactory::instance()->createTLVObject(TLV_TYPE_STRING);
	CPPUNIT_ASSERT_EQUAL(typeid(TLVString).name(), typeid(*obj).name());
	delete obj;

	obj = TLVObjectFactory::instance()->createTLVObject(TLV_TYPE_COMMAND_BASE);
	CPPUNIT_ASSERT_EQUAL(typeid(TLVCommand).name(), typeid(*obj).name());
	delete obj;
}

void TLVObjectFactoryTestSuite::testCreateByName()
{
	ITLVObject *obj = TLVObjectFactory::instance()->createTLVObject(typeid(TLVUInt16).name());
	CPPUNIT_ASSERT_EQUAL(typeid(TLVUInt16).name(), typeid(*obj).name());
	delete obj;

	obj = TLVObjectFactory::instance()->createTLVObject(typeid(TLVUInt32).name());
	CPPUNIT_ASSERT_EQUAL(typeid(TLVUInt32).name(), typeid(*obj).name());
	delete obj;

	obj = TLVObjectFactory::instance()->createTLVObject(typeid(TLVString).name());
	CPPUNIT_ASSERT_EQUAL(typeid(TLVString).name(), typeid(*obj).name());
	delete obj;

	obj = TLVObjectFactory::instance()->createTLVObject(typeid(TLVCommand).name());
	CPPUNIT_ASSERT_EQUAL(typeid(TLVCommand).name(), typeid(*obj).name());
	delete obj;
}

void TLVObjectFactoryTestSuite::testCreateByTLVBlock()
{
	ITLVBlock *blk = TLVUInt16().toTLVBlock();
	ITLVObject *obj = TLVObjectFactory::instance()->createTLVObject(*blk);
	CPPUNIT_ASSERT_EQUAL(typeid(TLVUInt16).name(), typeid(*obj).name());
	delete obj;
	delete blk;

	blk = TLVUInt32().toTLVBlock();
	obj = TLVObjectFactory::instance()->createTLVObject(*blk);
	CPPUNIT_ASSERT_EQUAL(typeid(TLVUInt32).name(), typeid(*obj).name());
	delete obj;
	delete blk;

	blk = TLVString().toTLVBlock();
	obj = TLVObjectFactory::instance()->createTLVObject(*blk);
	CPPUNIT_ASSERT_EQUAL(typeid(TLVString).name(), typeid(*obj).name());
	delete obj;
	delete blk;

	blk = TLVCommand().toTLVBlock();
	obj = TLVObjectFactory::instance()->createTLVObject(*blk);
	CPPUNIT_ASSERT_EQUAL(typeid(TLVCommand).name(), typeid(*obj).name());
	delete obj;
	delete blk;
}
