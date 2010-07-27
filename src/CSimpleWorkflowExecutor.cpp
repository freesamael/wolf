/**
 * \file CSimpleWorkflowExecutor.cpp
 * \date Mar 25, 2010
 * \author samael
 */
#include <unistd.h>
#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "CSimpleWorkflowExecutor.h"

using namespace std;

namespace wolf
{

void CSimpleWorkflowExecutor::execute(const vector<AActor *> &actors)
{
	_all = actors;
	setPriority(minimumPriority());
	start();
	join();
}

void CSimpleWorkflowExecutor::run()
{
	setup();
	iterate();
	wrapup();
}

void CSimpleWorkflowExecutor::setup()
{
	for (unsigned i = 0; i < _all.size(); i++)
		_all[i]->setup();
}

void CSimpleWorkflowExecutor::iterate()
{
	_vwaitready = _all;

	findready();
	while (!(_vwaitready.empty() && _vwaitpost.empty() &&
			_qready.empty() && _qpost.empty())) {
		// Run all ready actors.
		while (!_qready.empty()) {
			AActor *a = _qready.front();
			_qready.pop_front();
			runactor(a);
		}
		findpost();

		// Postrun all postrunning actors.
		while (!_qpost.empty()) {
			AActor *a = _qpost.front();
			_qpost.pop_front();
			postrunactor(a);
		}
		findready();

		if (_qready.empty())
			usleep(10000);
	}

}

void CSimpleWorkflowExecutor::wrapup()
{
	for (unsigned i = 0; i < _all.size(); i++)
		_all[i]->wrapup();
}

void CSimpleWorkflowExecutor::findready()
{
	static int prcount = 0;
	static unsigned pwcount = 0;
	int rcount = 0;
	vector<AActor *>::iterator iter;
	for (iter = _vwaitready.begin(); iter != _vwaitready.end();) {
		if ((*iter)->state() == AActor::READY) {
			_qready.push_back(*iter);
			_vwaitready.erase(iter);
			rcount++;
		} else
			++iter;
	}

	if (rcount != prcount || _vwaitready.size() != pwcount) {
		PINF_3("Found " << rcount << " runners ready, " << _vwaitready.size() <<
			" actors are still waiting.");
	}

	prcount = rcount;
	pwcount = _vwaitready.size();
}

void CSimpleWorkflowExecutor::findpost()
{
	static int ppcount = 0;
	static unsigned pwcount = 0;
	int pcount = 0;
	vector<AActor *>::iterator iter;
	for (iter = _vwaitpost.begin(); iter != _vwaitpost.end();) {
		if ((*iter)->state() == AActor::POST_RUNNING) {
			_qpost.push_back(*iter);
			_vwaitpost.erase(iter);
			pcount++;
		} else
			++iter;
	}

	if (pcount != ppcount || _vwaitpost.size() != pwcount) {
		PINF_3("Found " << pcount << " runners postrunning, " <<
				_vwaitpost.size() << " actors are still waiting.");
	}

	ppcount = pcount;
	pwcount = _vwaitpost.size();
}

void CSimpleWorkflowExecutor::runactor(AActor *actor)
{
	actor->prefire();
	actor->fire();
	_vwaitpost.push_back(actor);
}

void CSimpleWorkflowExecutor::postrunactor(AActor *actor)
{
	actor->postfire();
	if (actor->testfire())
		_qready.push_back(actor);
}

}
