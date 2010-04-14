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

void SimpleWorkflowExecutor::execute(const vector<AbstractActor *> &actors)
{
	setup(actors);
	iterate(actors);
	wrapup(actors);
}

void SimpleWorkflowExecutor::setup(const vector<AbstractActor *> &actors)
{
	for (int i = 0; i < (int)actors.size(); i++)
		actors[i]->setup();
}

void SimpleWorkflowExecutor::iterate(const vector<AbstractActor *> &actors)
{
	deque<AbstractActor *> qready;
	vector<AbstractActor *> vwait = actors;
	vector<AbstractActor *>::iterator iter;

	// Put ready actors into ready queue.
	for (iter = vwait.begin(); iter != vwait.end();) {
		if ((*iter)->state() == AbstractActor::READY) {
			qready.push_back(*iter);
			vwait.erase(iter);
		} else
			iter++;
	}

	// Execute one actor.
	while (qready.size() > 0) {
		// Iterate until testfire() fails.
		do {
			qready.front()->prefire();
			qready.front()->fire();
			qready.front()->postfire();
		} while (qready.front()->testfire());
		qready.pop_front();

		// Put ready actors into ready queue.
		for (iter = vwait.begin(); iter != vwait.end();) {
			if ((*iter)->state() == AbstractActor::READY) {
				qready.push_back(*iter);
				vwait.erase(iter);
			} else
				iter++;
		}
	}
}

void SimpleWorkflowExecutor::wrapup(const vector<AbstractActor *> &actors)
{
	for (int i = 0; i < (int)actors.size(); i++)
		actors[i]->wrapup();
}

}
