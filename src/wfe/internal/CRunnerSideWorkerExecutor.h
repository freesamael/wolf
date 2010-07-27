/**
 * \file CRunnerSideWorkerExecutor.h
 * \date May 26, 2010
 * \author samael
 */

#ifndef CRUNNERSIDEWORKEREXECUTOR_H_
#define CRUNNERSIDEWORKEREXECUTOR_H_

#include "CThread.h"
#include "CMutex.h"
#include "CRunner.h"

namespace wolf
{

/**
 * Used by runner to execute workers.
 */
class CRunnerSideWorkerExecutor: public wolf::CThread
{
public:
	CRunnerSideWorkerExecutor(CRunner *runner):
		_done(false), _runner(runner), _mx() {}
	CRunnerSideWorkerExecutor(const CRunnerSideWorkerExecutor &o):
		wolf::CThread(), _done(o._done), _runner(o._runner), _mx() {}
	CRunnerSideWorkerExecutor& operator=(const CRunnerSideWorkerExecutor &o)
		{ _done = o._done; _runner = o._runner; return *this; }
	inline bool isDone()
		{ _mx.lock(); bool d = _done; _mx.unlock(); return d; }
	inline void setDone(bool d = true)
		{ _mx.lock(); _done = d; _mx.unlock(); }
	void run();

private:
	bool _done;
	CRunner* _runner;
	wolf::CMutex _mx;
};

}

#endif /* CRUNNERSIDEWORKEREXECUTOR_H_ */
