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
#include <TLVMessage.h>
#include <CmlTLVTypes.h>
#include <TLVBlock.h>
#include <WfeTLVTypes.h>
#include "TLVObjectFactoryTestSuite.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TLVObjectFactoryTestSuite);

using namespace std;
using namespace cml;
using namespace wfe;

void TLVObjectFactoryTestSuite::testLookupId()
{
	CPPUNIT_ASSERT_EQUAL((unsigned short)TLV_TYPE_UINT16,
			TLVObjectFactory::instance()->lookupTypeId(typeid(TLVUInt16).name()));
	CPPUNIT_ASSERT_EQUAL((unsigned short)TLV_TYPE_UINT32,
			TLVObjectFactory::instance()->lookupTypeId(typeid(TLVUInt32).name()));
	CPPUNIT_ASSERT_EQUAL((unsigned short)TLV_TYPE_STRING,
			TLVObjectFactory::instance()->lookupTypeId(typeid(TLVString).name()));
	CPPUNIT_ASSERT_EQUAL((unsigned short)TLV_TYPE_MESSAGE_BASE,
			TLVObjectFactory::instance()->lookupTypeId(typeid(TLVMessage).name()));
}

void TLVObjectFactoryTestSuite::testLookupName()
{
	CPPUNIT_ASSERT_EQUAL((string)typeid(TLVUInt16).name(),
			(string)TLVObjectFactory::instance()->lookupTypeName(TLV_TYPE_UINT16));
	CPPUNIT_ASSERT_EQUAL((string)typeid(TLVUInt32).name(),
			(string)TLVObjectFactory::instance()->lookupTypeName(TLV_TYPE_UINT32));
	CPPUNIT_ASSERT_EQUAL((string)typeid(TLVString).name(),
			(string)TLVObjectFactory::instance()->lookupTypeName(TLV_TYPE_STRING));
	CPPUNIT_ASSERT_EQUAL((string)typeid(TLVMessage).name(),
			(string)TLVObjectFactory::instance()->lookupTypeName(TLV_TYPE_MESSAGE_BASE));
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

	obj = TLVObjectFactory::instance()->createTLVObject(TLV_TYPE_MESSAGE_BASE);
	CPPUNIT_ASSERT_EQUAL(typeid(TLVMessage).name(), typeid(*obj).name());
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

	obj = TLVObjectFactory::instance()->createTLVObject(typeid(TLVMessage).name());
	CPPUNIT_ASSERT_EQUAL(typeid(TLVMessage).name(), typeid(*obj).name());
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

	blk = TLVMessage().toTLVBlock();
	obj = TLVObjectFactory::instance()->createTLVObject(*blk);
	CPPUNIT_ASSERT_EQUAL(typeid(TLVMessage).name(), typeid(*obj).name());
	delete obj;
	delete blk;
}
