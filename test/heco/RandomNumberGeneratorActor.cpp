/*
 * RandomNumberGeneratorActor.cpp
 *
 *  Created on: Apr 9, 2010
 *      Author: samael
 */

#include <iostream>
#include <cstdio>
#include <ctime>
#include <D2MCE.h>
#include "RandomNumberGeneratorActor.h"

using namespace std;
using namespace cml;
using namespace wfe;

RandomNumberGeneratorActor::RandomNumberGeneratorActor()
{
	srand(time(NULL));
	_outports.push_back(new Port(this));
}

IActor::State RandomNumberGeneratorActor::state()
{
	if (_state == NOT_READY && isInputReady())
		_state = READY;
	return _state;
}

void RandomNumberGeneratorActor::fire()
{
	SharedMemory *sm = D2MCE::instance()->createSharedMemory("rand", sizeof(int));
	int n = 1000;
	*reinterpret_cast<int *>(sm->buffer()) = n;
	sm->store();
	_outports[0]->channel()->setSharedMemory(sm);
	cout << "Number Generated = " << n << endl;
}
