/**
 * \file Thread.h
 * \date Mar 9, 2010
 * \author samael
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include "IRunnable.h"

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
	bool start();
	bool join();
	bool join(unsigned timeout);
	bool cancel();

private:
	IRunnable *_runner;
	pthread_cond_t _rcnd;
	pthread_mutex_t _rcnd_mutex;
	pthread_t _tid;
	bool _running;
};

}

#endif /* THREAD_H_ */
