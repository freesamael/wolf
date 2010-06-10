/**
 * \file ConcurrentWorkflowExecutor.cpp
 * \date Jun 10, 2010
 * \author samael
 */

#include <unistd.h>
#include "ConcurrentWorkflowExecutor.h"

using namespace std;
using namespace cml;

namespace wfe
{

/**
 * An executor to iterate the actor.
 */
class Executor: public IRunnable
{
public:
	Executor(ConcurrentWorkflowExecutor *parent): _p(parent) {}
	Executor(const Executor &o): _p(o._p) {}
	Executor& operator=(const Executor &o) { _p = o._p; return *this; }
	void run() {
		while (!_p->isFinished()) {
			AbstractActor *actor;
			if ((actor = _p->takeActor())) {
				PINFO_2("Iterating an actor.");
				do {
					actor->prefire();
					actor->fire();
					actor->postfire();
				} while (actor->testfire());
				_p->updateQueue();
			}
		}
	}

private:
	ConcurrentWorkflowExecutor *_p;
};

ConcurrentWorkflowExecutor::ConcurrentWorkflowExecutor(unsigned pnum):
		_fin(false), _exths(), _vwait(), _qready(), _mutex(), _wcond()
{
	for (unsigned i = 0; i < pnum; i++)
		_exths.push_back(new Thread(new Executor(this)));
}

ConcurrentWorkflowExecutor::~ConcurrentWorkflowExecutor()
{
	for (unsigned i = 0; i < _exths.size(); i++) {
		delete _exths[i]->runner();
		delete _exths[i];
	}
}

void ConcurrentWorkflowExecutor::execute(const vector<AbstractActor *> &actors)
{
	setup(actors);
	wrapup(actors);
}

void ConcurrentWorkflowExecutor::updateQueue()
{
	_mutex.lock();

	vector<AbstractActor *>::iterator iter;

	// Put ready actors into ready queue.
	for (iter = _vwait.begin(); iter != _vwait.end();) {
		if ((*iter)->state() == AbstractActor::READY) {
			_qready.push_back(*iter);
			_vwait.erase(iter);
			_wcond.wakeOne();
		} else
			iter++;
	}

	// No more actors to run => finish, wake up all executors.
	if (_vwait.size() == 0 && _qready.size() == 0) {
		_fin = true;
		_wcond.wakeAll();
	}

	_mutex.unlock();
}

AbstractActor* ConcurrentWorkflowExecutor::takeActor()
{
	AbstractActor *actor = NULL;

	_mutex.lock();

	// Wait if no ready actors.
	if (_qready.size() == 0)
		_wcond.wait(&_mutex);

	// Take the first ready actor (if any).
	if (_qready.size() > 0) {
		actor = _qready.front();
		_qready.pop_front();
	}

	_mutex.unlock();

	return actor;
}

void ConcurrentWorkflowExecutor::setup(const vector<AbstractActor *> &actors)
{
	// Setup all runners.
	for (unsigned i = 0; i < actors.size(); i++)
		actors[i]->setup();

	// Prepare waiting/ready queues.
	_vwait = actors;
	updateQueue();

	// Start iterating.
	for (unsigned i = 0; i < _exths.size(); i++)
		_exths[i]->start();
}

void ConcurrentWorkflowExecutor::wrapup(const vector<AbstractActor *> &actors)
{
	// Wait all iterations finish.
	for (unsigned i = 0; i < _exths.size(); i++)
		_exths[i]->join();

	// Wrapup all actors.
	for (unsigned i = 0; i < actors.size(); i++)
		actors[i]->wrapup();
}

}
