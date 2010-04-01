/*
 * testmaster.cpp
 *
 *  Created on: Mar 31, 2010
 *      Author: samael
 */

#include <iostream>
#include <typeinfo>
#include <TLVObjectFactory.h>
#include <RunnerAgent.h>
#include <CustomTLVTypes.h>
#include <TLVMessageCreator.h>

using namespace std;
using namespace cml;
using namespace wfe;

int main()
{
	TLVObjectFactory::instance()->registerType(typeid(TLVMessage).name(),
			TLV_TYPE_MESSAGE);
	TLVObjectFactory::instance()->registerCreator(typeid(TLVMessage).name(),
			new TLVMessageCreator());

	cout << RunnerAgent::instance()->setup(5566, 7788, 2000000) << endl;

	RunnerAgent::release();
	TLVObjectFactory::instance()->release();

	return 0;
}
