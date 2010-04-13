/**
 * \file ManagerActor.cpp
 * \date Apr 13, 2010
 * \author samael
 */

#include "ManagerActor.h"

namespace wfe
{

ManagerActor::ManagerActor(IWorkerActor *worker):
		_worker(worker), _firecond(true)
{
	_worker->initialize(this);
}

ManagerActor::~ManagerActor()
{
	 _worker->finalize(this);
	 for (int i = 0; i < (int)_sinp.size(); i++)
		 delete _sinp[i];
	 for (int i = 0; i < (int)_srcp.size(); i++)
		 delete _srcp[i];
}

void ManagerActor::setup()
{

}

void ManagerActor::wrapup()
{

}

bool ManagerActor::testfire()
{
	return _firecond;
}

void ManagerActor::prefire()
{

}

void ManagerActor::fire()
{

}

void ManagerActor::postfire()
{
	_firecond = false;
}

SinkPort* ManagerActor::addSinkPort()
{
	SinkPort *p = new SinkPort(this);
	_sinp.push_back(p);
	return p;
}

SourcePort* ManagerActor::addSourcePort()
{
	SourcePort *p = new SourcePort(this);
	_srcp.push_back(p);
	return p;
}

}
