/*
 * NumberSubstractorWorker.cpp
 *
 *  Created on: Apr 9, 2010
 *      Author: samael
 */

#include <iostream>
#include <vector>
#include <TLVObjectFactoryAutoRegistry.h>
#include <HelperMacros.h>
#include <D2MCE.h>
#include "NumberSubstractorWorker.h"
#include "NumberSubstractorWorkerCreator.h"

using namespace std;
using namespace wfe;
using namespace cml;

#define TLV_TYPE_SUBBER	20

TLV_OBJECT_REGISTRATION(NumberSubstractorWorker, TLV_TYPE_SUBBER,
		NumberSubstractorWorkerCreator);

StandardTLVBlock* NumberSubstractorWorker::toTLVBlock() const
{
	if (_sminfo) {
		vector<const ITLVBlock *> blocks;

		blocks.push_back(_sminfo->toTLVBlock());
		StandardTLVBlock *blk = StandardTLVBlock::concate(blocks);
		blk->setType(TLV_TYPE_SUBBER);

		delete blocks[0];
		return blk;
	}
	return new StandardTLVBlock(TLV_TYPE_SUBBER, 0);
}

void NumberSubstractorWorker::prefire()
{
	cout << "Worker: prefire()" << endl;
	_firecount = 0;
	_sm = D2MCE::instance()->createSharedMemory(_sminfo->name(),
			_sminfo->size());
	_sm->lock();
	_sm->load();
	cout << "Worker: number = " << *reinterpret_cast<int *>(_sm->buffer()) << endl;
	_sm->unlock();
}

void NumberSubstractorWorker::fire()
{
	cout << "Worker: fire()" << endl;
	_sm->lock();
	_sm->load();
	(*reinterpret_cast<int *>(_sm->buffer()))--;
	_firecount++;
	_sm->store();
	_sm->unlock();
}

void NumberSubstractorWorker::postfire()
{
	cout << "Worker: postfire()" << endl;
	cout << "Worker: number = " << *reinterpret_cast<int *>(_sm->buffer()) << endl;
	D2MCE::instance()->barrier((unsigned)D2MCE::instance()->getNumberOfNodes());
}
