/**
 * \file SimpleWorkflowExecutor.cpp
 * \date Mar 25, 2010
 * \author samael
 */

#include <deque>
#include "SimpleWorkflowExecutor.h"

using namespace std;

namespace wfe
{

void SimpleWorkflowExecutor::execute(const vector<IActor *> &actors)
{
	setup(actors);
	iterate(actors);
	wrapup(actors);
}

void SimpleWorkflowExecutor::setup(const vector<IActor *> &actors)
{
	for (int i = 0; i < (int)actors.size(); i++)
		actors[i]->setup();
}

void SimpleWorkflowExecutor::iterate(const vector<IActor *> &actors)
{
	deque<IActor *> qready;
	vector<IActor *> vwait = actors;
	vector<IActor *>::iterator iter;

	// Put ready actors into ready queue.
	for (iter = vwait.begin(); iter != vwait.end();) {
		if ((*iter)->state() == IActor::READY) {
			qready.push_back(*iter);
			vwait.erase(iter);
		} else
			iter++;
	}

	// Execute one actor.
	while (qready.size() > 0) {
		// Iterate until testfire() fails.
		while (qready.front()->testfire()) {
			qready.front()->prefire();
			qready.front()->fire();
			qready.front()->postfire();
		}
		qready.pop_front();

		// Put ready actors into ready queue.
		for (iter = vwait.begin(); iter != vwait.end();) {
			if ((*iter)->state() == IActor::READY) {
				qready.push_back(*iter);
				vwait.erase(iter);
			} else
				iter++;
		}
	}
}

void SimpleWorkflowExecutor::wrapup(const vector<IActor *> &actors)
{
	for (int i = 0; i < (int)actors.size(); i++)
		actors[i]->wrapup();
}

}
