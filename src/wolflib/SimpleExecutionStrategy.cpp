/*
 * SimpleExecutionStrategy.cpp
 *
 *  Created on: Mar 25, 2010
 *      Author: samael
 */

#include <deque>
#include "SimpleExecutionStrategy.h"
#include "AbstractActor.h"
#include "AbstractIterativeActor.h"

using namespace std;

namespace wfe
{

void SimpleExecutionStrategy::execute(const vector<AbstractActor*> &actors)
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
		AbstractIterativeActor *itatr;
		if ((itatr = dynamic_cast<AbstractIterativeActor*>(qready.front()))) {
			while (itatr->fireCond()) {
				itatr->preFire();
				itatr->fire();
				itatr->postFire();
			}
		} else {
			qready.front()->preFire();
			qready.front()->fire();
			qready.front()->postFire();
		}
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

}
