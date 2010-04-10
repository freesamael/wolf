/*
 * NumberReaderActor.cpp
 *
 *  Created on: Apr 9, 2010
 *      Author: samael
 */

#include <iostream>
#include <SharedMemory.h>
#include "NumberReaderActor.h"

using namespace std;
using namespace cml;
using namespace wfe;

IActor::State NumberReaderActor::state()
{
	if (_state == NOT_READY && isInputReady())
		_state = READY;
	return _state;
}

void NumberReaderActor::fire()
{
	SharedMemory *sm = _inports[0]->channel()->read();
	int n = *reinterpret_cast<int *>(sm->buffer());
	cout << "Number Loaded = " << n << endl;
}
