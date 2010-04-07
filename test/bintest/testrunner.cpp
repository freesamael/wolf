/*
 * testrunner.cpp
 *
 *  Created on: Apr 1, 2010
 *      Author: samael
 */

#include <typeinfo>
#include <TLVObjectFactory.h>
#include <TLVMessageCreator.h>
#include <TLVMessage.h>
#include <Runner.h>
#include <CustomTLVTypes.h>
#include "testactors.h"

using namespace std;
using namespace cml;
using namespace wfe;

int main()
{
	Runner runner;
	runner.run(5566, 7788);

	TLVObjectFactory::release();

	return 0;
}
