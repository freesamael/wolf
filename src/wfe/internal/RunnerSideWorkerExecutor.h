/**
 * \file RunnerSideWorkerExecutor.h
 * \date May 26, 2010
 * \author samael
 */

#ifndef RUNNERSIDEWORKEREXECUTOR_H_
#define RUNNERSIDEWORKEREXECUTOR_H_

#include "IRunnable.h"
#include "Mutex.h"
#include "Runner.h"

namespace wfe
{

/**
 * Used by runner to execute workers.
 */
class RunnerSideWorkerExecutor: public cml::IRunnable
{
public:
	RunnerSideWorkerExecutor(Runner *runner):
		_done(false), _runner(runner), _mx() {}
	RunnerSideWorkerExecutor(const RunnerSideWorkerExecutor &o):
		_done(o._done), _runner(o._runner), _mx() {}
	RunnerSideWorkerExecutor& operator=(const RunnerSideWorkerExecutor &o)
		{ _done = o._done; _runner = o._runner; return *this; }
	inline bool isDone()
		{ _mx.lock(); bool d = _done; _mx.unlock(); return d; }
	inline void setDone(bool d = true)
		{ _mx.lock(); _done = d; _mx.unlock(); }
	void run();

private:
	bool _done;
	Runner* _runner;
	cml::Mutex _mx;
};

}

#endif /* RUNNERSIDEWORKEREXECUTOR_H_ */
