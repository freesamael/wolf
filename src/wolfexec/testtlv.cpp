/*
 * testtlv.cpp
 *
 *  Created on: Mar 28, 2010
 *      Author: samael
 */

#include <iostream>
#include "TLVBlock.h"
#include "TLVString.h"
#include "TLVUInt16.h"
#include "TLVUInt32.h"
#include "TLVObjectFactory.h"

using namespace cml;
using namespace std;

int main()
{
	// Test String
	TLVString str("Hello World!");
	TLVBlock *blk = str.toTLVBlock();
	TLVString *ostr = (TLVString *)TLVObjectFactory::instance()->
			createTLVObject(*blk);

	cout << ostr->toString() << endl;

	delete blk;
	delete ostr;

	// Test UInt16
	TLVUInt16 ui16(155);
	blk = ui16.toTLVBlock();
	TLVUInt16 *oui16 = (TLVUInt16 *)TLVObjectFactory::instance()->
			createTLVObject(*blk);

	cout << oui16->value() << endl;

	delete blk;
	delete oui16;

	// Test UInt32
	TLVUInt32 ui32(16777216);
	blk = ui32.toTLVBlock();
	TLVUInt32 *oui32 = (TLVUInt32 *)TLVObjectFactory::instance()->
			createTLVObject(*blk);

	cout << oui32->value() << endl;

	delete blk;
	delete oui32;

	return 0;
}
