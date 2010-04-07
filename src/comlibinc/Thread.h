/*
 * Thread.h
 *
 *  Created on: Mar 9, 2010
 *      Author: samael
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

namespace cml
{

/**
 * Pthread wrapper.
 */
class Thread
{
public:
	Thread();
	virtual ~Thread();
	virtual void run() = 0;
	inline pthread_t threadID() const { return _tid; }
	bool start();
	bool join();
	bool join(unsigned timeout);
	bool cancel();

private:
	static void* _thread_caller(void *param);
	pthread_cond_t _rcnd;
	pthread_mutex_t _rcnd_mutex;
	pthread_t _tid;
	bool _running;
};

}

#endif /* THREAD_H_ */
