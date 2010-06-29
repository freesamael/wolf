/**
 * \file SimpleWorkflowExecutor.cpp
 * \date Mar 25, 2010
 * \author samael
 */
#include <unistd.h>
#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "SimpleWorkflowExecutor.h"

using namespace std;

namespace wfe
{

void SimpleWorkflowExecutor::execute(const vector<AbstractActor *> &actors)
{
	_all = actors;
	setPriority(minimumPriority());
	start();
	join();
}

void SimpleWorkflowExecutor::run()
{
	setup();
	iterate();
	wrapup();
}

void SimpleWorkflowExecutor::setup()
{
	PINF_2("Setup all runners.");
	for (unsigned i = 0; i < _all.size(); i++)
		_all[i]->setup();
}

void SimpleWorkflowExecutor::iterate()
{
	_vwaitready = _all;

	findready();
	while (!(_vwaitready.empty() && _vwaitpost.empty() &&
			_qready.empty() && _qpost.empty())) {
		// Run all ready actors.
		while (!_qready.empty()) {
			AbstractActor *a = _qready.front();
			_qready.pop_front();
			runactor(a);
		}
		findpost();

		// Postrun all postrunning actors.
		while (!_qpost.empty()) {
			AbstractActor *a = _qpost.front();
			_qpost.pop_front();
			postrunactor(a);
		}
		findready();

		if (_qready.empty())
			usleep(10000);
	}

	PINF_2("Execution loop ends.");
}

void SimpleWorkflowExecutor::wrapup()
{
	PINF_2("Wrapup all runners.");
	for (unsigned i = 0; i < _all.size(); i++)
		_all[i]->wrapup();
}

void SimpleWorkflowExecutor::findready()
{
	static int prcount = 0;
	static unsigned pwcount = 0;
	int rcount = 0;
	vector<AbstractActor *>::iterator iter;
	for (iter = _vwaitready.begin(); iter != _vwaitready.end();) {
		if ((*iter)->state() == AbstractActor::READY) {
			_qready.push_back(*iter);
			_vwaitready.erase(iter);
			rcount++;
		} else
			++iter;
	}

	if (rcount != prcount || _vwaitready.size() != pwcount) {
		PINF_2("Found " << rcount << " runners ready, " << _vwaitready.size() <<
			" actors are still waiting.");
	}

	prcount = rcount;
	pwcount = _vwaitready.size();
}

void SimpleWorkflowExecutor::findpost()
{
	static int ppcount = 0;
	static unsigned pwcount = 0;
	int pcount = 0;
	vector<AbstractActor *>::iterator iter;
	for (iter = _vwaitpost.begin(); iter != _vwaitpost.end();) {
		if ((*iter)->state() == AbstractActor::POST_RUNNING) {
			_qpost.push_back(*iter);
			_vwaitpost.erase(iter);
			pcount++;
		} else
			++iter;
	}

	if (pcount != ppcount || _vwaitpost.size() != pwcount) {
		PINF_2("Found " << pcount << " runners postrunning, " <<
				_vwaitpost.size() << " actors are still waiting.");
	}

	ppcount = pcount;
	pwcount = _vwaitpost.size();
}

void SimpleWorkflowExecutor::runactor(AbstractActor *actor)
{
	PINF_2("Executing an actor.");
	actor->prefire();
	actor->fire();
	_vwaitpost.push_back(actor);
}

void SimpleWorkflowExecutor::postrunactor(AbstractActor *actor)
{
	PINF_2("Postrunning an actor.");
	actor->postfire();
	if (actor->testfire())
		_qready.push_back(actor);
}

}
