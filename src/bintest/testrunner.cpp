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
	// Register TLVMessage.
	TLVObjectFactory::instance()->registerType(typeid(TLVMessage).name(),
			TLV_TYPE_MESSAGE);
	TLVObjectFactory::instance()->registerCreator(typeid(TLVMessage).name(),
			new TLVMessageCreator());

	// Register TestActor.
	TLVObjectFactory::instance()->registerType(typeid(TestActor).name(),
			TLV_TYPE_TEST_ACTOR);
	TLVObjectFactory::instance()->registerCreator(typeid(TestActor).name(),
			new TestActorCreator());

	Runner runner;
	runner.run(5566, 7788);

	TLVObjectFactory::release();

	return 0;
}
