/*
 * testtlv.cpp
 *
 *  Created on: Mar 28, 2010
 *      Author: samael
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <typeinfo>
#include "TLVBlock.h"
#include "TLVString.h"
#include "TLVUInt16.h"
#include "TLVUInt32.h"
#include "TLVMessage.h"
#include "TLVMessageCreator.h"
#include "TLVObjectFactory.h"
#include "CustomTLVTypes.h"

using namespace cml;
using namespace wfe;
using namespace std;

void test_tlvblock()
{
	StandardTLVBlock blk;
	blk.setType(5566);
	blk.setLength(8080);

	printf("Type = 0x%x, Length = 0x%x\n", blk.type(), blk.length());
	printf("Type (Native) = 0x%x, Length (Native) = 0x%x\n",
			((unsigned short *)blk.plainBuffer())[0],
			((unsigned short *)blk.plainBuffer())[1]);
}

void test_tlvstring()
{
	// Test String.
	TLVString str("Hello World!");
	StandardTLVBlock *blk = str.toTLVBlock();
	TLVString *ostr = (TLVString *)TLVObjectFactory::instance()->
			createTLVObject(*blk);

	cout << ostr->toString() << endl;

	delete blk;
	delete ostr;
}

void test_tlvuint16()
{
	// Test UInt16.
	TLVUInt16 ui16(155);
	StandardTLVBlock *blk = ui16.toTLVBlock();
	TLVUInt16 *oui16 = (TLVUInt16 *)TLVObjectFactory::instance()->
			createTLVObject(*blk);

	cout << oui16->value() << endl;

	delete blk;
	delete oui16;
}

void test_tlvuint32()
{
	// Test UInt32.
	TLVUInt32 ui32(16777216);
	StandardTLVBlock *blk = ui32.toTLVBlock();
	TLVUInt32 *oui32 = (TLVUInt32 *)TLVObjectFactory::instance()->
			createTLVObject(*blk);

	cout << oui32->value() << endl;

	delete blk;
	delete oui32;
}

void register_tlvmsg()
{
	// Register types/creators.
	TLVObjectFactory::instance()->registerType(typeid(TLVMessage).name(),
			TLV_TYPE_MESSAGE);
	TLVObjectFactory::instance()->registerCreator(typeid(TLVMessage).name(),
			new TLVMessageCreator());
}

void test_tlvmsg()
{
	// Test Message.
	TLVMessage msg(TLVMessage::EMPTY);
	StandardTLVBlock *blk = msg.toTLVBlock();
	TLVMessage *omsg = (TLVMessage *)TLVObjectFactory::instance()->
			createTLVObject(*blk);

	cout << TLVMessage::CommandString[omsg->command()] << endl;

	delete blk;
	delete omsg;
}

int main()
{
	test_tlvblock();
	test_tlvstring();
	test_tlvuint16();
	test_tlvuint32();
	register_tlvmsg();
	test_tlvmsg();
	return 0;
}
