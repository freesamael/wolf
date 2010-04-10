/*
 * NumberSubstractorManager.cpp
 *
 *  Created on: Apr 9, 2010
 *      Author: samael
 */

#include <cstring>
#include <Port.h>
#include <TLVSharedMemoryInfo.h>
#include <Channel.h>
#include <D2MCE.h>
#include "NumberSubstractorManager.h"
#include "NumberSubstractorWorker.h"

using namespace cml;
using namespace wfe;

NumberSubstractorManager::NumberSubstractorManager()
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
	_sm = D2MCE::instance()->createSharedMemory("sub",
			_inports[0]->channel()->read()->size());
	memcpy(_sm->buffer(), _inports[0]->channel()->read()->buffer(),
			_sm->size());
	_sm->store();

	_workers.push_back(new NumberSubstractorWorker(
			new TLVSharedMemoryInfo(_sm->name(), _sm->size())));
	_state = RUNNING;
}

void NumberSubstractorManager::postfire()
{
	D2MCE::instance()->barrier((unsigned)D2MCE::instance()->getNumberOfNodes());
	_sm->load();
	_outports[0]->channel()->write(_sm);
	_state = FINISHED;
}
