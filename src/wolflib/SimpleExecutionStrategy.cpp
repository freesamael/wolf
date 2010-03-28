/*
 * SimpleExecutionStrategy.cpp
 *
 *  Created on: Mar 25, 2010
 *      Author: samael
 */

#include <deque>
#include "SimpleExecutionStrategy.h"

using namespace std;

namespace wfe
{

void SimpleExecutionStrategy::execute(const vector<IActor *> &actors)
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
		qready.front()->prefire();
		qready.front()->fire();
		qready.front()->postfire();
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

}
