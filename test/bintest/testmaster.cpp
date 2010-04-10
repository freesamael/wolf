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
#include <WfeTLVTypes.h>
#include <TLVMessageCreator.h>
#include "testactors.h"

using namespace std;
using namespace cml;
using namespace wfe;

int main()
{
	TestActor actor;

	RunnerAgent::instance()->setup(5566, 7788, "test", 2);
//	cout << RunnerAgent::instance()->sendActor(&actor) << endl;
//	cout << RunnerAgent::instance()->sendActor(&actor) << endl;
//	cout << RunnerAgent::instance()->sendActor(&actor) << endl;

	return 0;
}
