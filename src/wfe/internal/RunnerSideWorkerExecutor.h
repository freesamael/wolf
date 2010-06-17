/**
 * \file RunnerSideWorkerExecutor.h
 * \date May 26, 2010
 * \author samael
 */

#ifndef RUNNERSIDEWORKEREXECUTOR_H_
#define RUNNERSIDEWORKEREXECUTOR_H_

#include "IRunnable.h"
#include "Runner.h"

namespace wfe
{

/**
 * Used by runner to execute workers.
 */
class RunnerSideWorkerExecutor: public cml::IRunnable
{
public:
	RunnerSideWorkerExecutor(Runner *runner): _done(false), _runner(runner) {}
	RunnerSideWorkerExecutor(const RunnerSideWorkerExecutor &o):
		_done(o._done), _runner(o._runner) {}
	RunnerSideWorkerExecutor& operator=(const RunnerSideWorkerExecutor &o)
		{ _done = o._done; _runner = o._runner; return *this; }
	inline bool isDone() const { return _done; }
	inline void setDone(bool d = true) { _done = d; }
	void run();

private:
	bool _done;
	Runner* _runner;
};

}

#endif /* RUNNERSIDEWORKEREXECUTOR_H_ */
