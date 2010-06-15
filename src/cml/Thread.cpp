/**
 * \file Thread.cpp
 * \date Mar 9, 2010
 * \author samael
 */

#include <iostream>
#include <cstdio>
#include <errno.h>
#include <sys/time.h>
#include "Thread.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * \internal
 * A thread function adaptor.
 */
void* thread_caller(void *param)
{
	cml::Thread *th = reinterpret_cast<cml::Thread *>(param);

	pthread_mutex_lock(&th->_mutex);
	th->_running = true;
	pthread_mutex_unlock(&th->_mutex);

	PINF_3("Start running thread's run() function.");
	th->run();

	pthread_mutex_lock(&th->_mutex);
	th->_running = false;
	th->_finished = true;
	PINF_3("Thread finished.");
	pthread_mutex_unlock(&th->_mutex);

	if (pthread_cond_broadcast(&th->_rcnd) != 0)
		perror("Error: thread_caller()");
	return NULL;
}

Thread::Thread(IRunnable *runner):
		_runner(runner), _rcnd(), _mutex(),
		_tid(0), _running(false), _finished(false), _canceled(false)
{
	int state;
	pthread_mutex_init(&_mutex, NULL);
	pthread_cond_init(&_rcnd, NULL);
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &state);
}

Thread::~Thread()
{
	pthread_cond_destroy(&_rcnd);
	pthread_mutex_destroy(&_mutex);
}

/**
 * Create a thread to execute run().
 */
bool Thread::start()
{
	PINF_3("Starting the thread.");
	if (_tid == 0) {
		if (pthread_create(&_tid, NULL, thread_caller, this) != 0) {
			perror("Error: Thread::start()");
			return false;
		}
		return true;
	}
	PERR("Thread " << _tid << " is already started.");
	return false;
}

/**
 * Block wait until thread exits.
 *
 * \return
 * True on success, false on failure.
 */
bool Thread::join()
{
	if (pthread_join(_tid, NULL) != 0) {
		perror("Error: Thread::join()");
		return false;
	}
	return true;
}

/**
 * Block wait until thread exits or timeout.
 *
 * \param timeout
 * Timeout in microseconds.
 *
 * \return
 * True on success, false on failure (including timeout).
 */
bool Thread::join(unsigned timeout)
{
	struct timeval now, abs_tout;
	struct timeval rel_tout = {timeout / 1000000, timeout % 1000000};
	struct timespec tout;

	// Set time.
	gettimeofday(&now, NULL);
	timeradd(&now, &rel_tout, &abs_tout);
	tout.tv_sec = abs_tout.tv_sec;
	tout.tv_nsec = abs_tout.tv_usec * 1000;

	pthread_mutex_lock(&_mutex);
	if (_running) {
		// Wait.
		if (pthread_cond_timedwait(&_rcnd, &_mutex, &tout) != 0) {
			perror("Error: Thread::join(): Condition waiting");
			return false;
		}
	}
	pthread_mutex_unlock(&_mutex);

	return true;
}

/**
 * Request cancel for executing thread.
 *
 * \note
 * If the thread doesn't poll testcancel() in run(), it has no effect. It's the
 * characteristic of pthread.
 *
 * \return
 * True on success, false on failure.
 */
bool Thread::cancel()
{
	if (pthread_cancel(_tid)) {
		PINF_3("Thread canceled.");
		return _canceled = true;
	}
	PERR("Failed to cancel thread.");
	return false;
}

}
