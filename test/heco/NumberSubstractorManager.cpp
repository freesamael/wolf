/*
 * NumberSubstractorManager.cpp
 *
 *  Created on: Apr 9, 2010
 *      Author: samael
 */

#include <iostream>
#include <cstring>
#include <Port.h>
#include <TLVSharedMemoryInfo.h>
#include <Channel.h>
#include <D2MCE.h>
#include "NumberSubstractorManager.h"
#include "NumberSubstractorWorker.h"

using namespace std;
using namespace cml;
using namespace wfe;

NumberSubstractorManager::NumberSubstractorManager(IManagerWorkerExecutor *exec):
		AbstractManagerActor(exec)
{
	_inports.push_back(new Port(this));
	_outports.push_back(new Port(this));
}

IActor::State NumberSubstractorManager::state()
{
	if (_state == NOT_READY && isInputReady())
		_state = READY;
	return _state;
}

void NumberSubstractorManager::prefire()
{
	cout << "Manager: prefire()" << endl;
	_state = RUNNING;

	_sm = D2MCE::instance()->createSharedMemory("submem",
			_inports[0]->channel()->read()->size());
	_sm->lock();
	memcpy(_sm->buffer(), _inports[0]->channel()->read()->buffer(),
			_sm->size());
	_sm->store();
	_sm->unlock();

	_workers.push_back(new NumberSubstractorWorker(
			new TLVSharedMemoryInfo(_sm->name(), _sm->size())));

	AbstractManagerActor::prefire();
}

void NumberSubstractorManager::fire()
{
	cout << "Manager: fire()" << endl;
	AbstractManagerActor::fire();
}

void NumberSubstractorManager::postfire()
{
	cout << "Manager: postfire()" << endl;
	D2MCE::instance()->barrier((unsigned)D2MCE::instance()->getNumberOfNodes());
	_sm->load();
	_outports[0]->channel()->write(_sm);
	_state = FINISHED;
}
