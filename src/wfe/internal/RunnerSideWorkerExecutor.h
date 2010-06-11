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
	RunnerSideWorkerExecutor(Runner *parent): _parent(parent) {}
	RunnerSideWorkerExecutor(const RunnerSideWorkerExecutor &o): _parent(o._parent) {}
	RunnerSideWorkerExecutor& operator=(const RunnerSideWorkerExecutor &o)
		{ _parent = o._parent; return *this; }
	void run();

private:
	Runner* _parent;
};

}

#endif /* RUNNERSIDEWORKEREXECUTOR_H_ */
