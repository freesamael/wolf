/*
 * SimpleManagerWorkerExecutor.cpp
 *
 *  Created on: Apr 4, 2010
 *      Author: samael
 */

#include "SimpleManagerWorkerExecutor.h"

using namespace std;

namespace wfe
{

void SimpleManagerWorkerExecutor::execute(const vector<AbstractWorkerActor *> &workers)
{
	for (int i = 0; i < (int)workers.size(); i++)
		_agent->sendActor(workers[i]);
}

}
