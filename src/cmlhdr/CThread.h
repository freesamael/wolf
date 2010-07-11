/**
 * \file CThread.h
 * \date Mar 9, 2010
 * \author samael
 */

#ifndef CTHREAD_H_
#define CTHREAD_H_

#include <pthread.h>
#include "IRunnable.h"
#include "CMutex.h"
#include "CWaitCondition.h"
#include "XThread.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * CThread represents an encapsulation of thread. It can be used in two ways -
 * by constructing a Thread with a given IRunnable, it executes IRunnable::run()
 * in a separate thread when start() is called; alternatively, a user can create
 * a subclass overriding run() to execute. In the later case, the runner is
 * ignored.
 */
class CThread
{
	friend void* thread_caller(void*);
public:
	CThread(IRunnable *runner = NULL) throw(XThread);
	virtual ~CThread();
	virtual inline void run() { if (_runner) _runner->run(); }
	inline pthread_t threadID() const { return _tid; }
	inline bool isRunning() const { return _running; }
	inline bool isFinished() const { return _finished; }
	inline bool isCanceled() const { return _canceled; }
	inline IRunnable* runner() const { return _runner; }
	void start() throw(XThread);
	bool join() throw(XThread);
	bool join(unsigned timeout_us) throw(XThread);
	void cancel() throw(XThread);
	int minimumPriority() throw(XThread);
	int maximumPriority() throw(XThread);
	int priority() throw(XThread);
	void setPriority(int p) throw(XThread);

private:
	CThread(const CThread &UNUSED(o)): _runner(NULL), _mutex(), _cond(),
		_tid(0), _tattr(), _tpoli(0), _tparm(), _running(false),
		_finished(false), _canceled(false) {}
	CThread& operator=(const CThread &UNUSED(o)) { return *this; }
	IRunnable *_runner;
	CMutex _mutex;
	CWaitCondition _cond;
	pthread_t _tid;
	pthread_attr_t _tattr;
	int _tpoli;
	sched_param _tparm;
	bool _running;
	bool _finished;
	bool _canceled;
};

}

#endif /* CTHREAD_H_ */
