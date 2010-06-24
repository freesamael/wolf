/**
 * \file Thread.h
 * \date Mar 9, 2010
 * \author samael
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include "IRunnable.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * Thread represents an encapsulation of thread. It can be used in two ways - by
 * construct a Thread with a given IRunnable, it executes IRunnable::run() in a
 * separate thread when start() is called; alternatively, a user can write a
 * subclass overriding run() to execute. In the later case, the IRunnable is
 * ignored.
 */
class Thread
{
	friend void* thread_caller(void*);
public:
	Thread(IRunnable *runner = NULL);
	virtual ~Thread();
	virtual inline void run() { if (_runner) _runner->run(); }
	inline pthread_t threadID() const { return _tid; }
	inline bool isRunning() const { return _running; }
	inline bool isFinished() const { return _finished; }
	inline bool isCanceled() const { return _canceled; }
	inline IRunnable* runner() const { return _runner; }
	bool start();
	bool join();
	bool join(unsigned timeout);
	bool cancel();
	int minimumPriority();
	int maximumPriority();
	int priority();
	bool setPriority(int p);

private:
	Thread(const Thread &UNUSED(o)): _runner(NULL), _rcnd(), _mutex(),
		_tid(0), _tattr(), _tpoli(0), _tparm(), _running(false),
		_finished(false), _canceled(false) {}
	Thread& operator=(const Thread &UNUSED(o)) { return *this; }
	IRunnable *_runner;
	pthread_cond_t _rcnd;
	pthread_mutex_t _mutex;
	pthread_t _tid;
	pthread_attr_t _tattr;
	int _tpoli;
	sched_param _tparm;
	bool _running;
	bool _finished;
	bool _canceled;
};

}

#endif /* THREAD_H_ */
