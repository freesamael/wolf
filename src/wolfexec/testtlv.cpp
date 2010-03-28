/*
 * testtlv.cpp
 *
 *  Created on: Mar 28, 2010
 *      Author: samael
 */

#include <iostream>
#include "TLVBlock.h"
#include "TLVString.h"
#include "TLVObjectFactory.h"

using namespace cml;
using namespace std;

int main()
{
	TLVString str("Hello World!");
	TLVBlock *blk = str.toTLVBlock();
	TLVString *ostr = (TLVString*)TLVObjectFactory::instance()->createTLVObject(*blk);

	cout << ostr->toString() << endl;

	delete blk;
	delete ostr;
	return 0;
}
