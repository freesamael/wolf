/**
 * \file CThread.cpp
 * \date Mar 9, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <cstdio>
#include <errno.h>
#include <sys/time.h>
#include "CThread.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * \internal
 * A thread function adaptor.
 */
void* thread_caller(void *param)
{
	cml::CThread *th = reinterpret_cast<cml::CThread *>(param);

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

CThread::CThread(IRunnable *runner):
		_runner(runner), _rcnd(), _mutex(),
		_tid(0), _tattr(), _tpoli(0), _tparm(), _running(false),
		_finished(false), _canceled(false)
{
	pthread_mutex_init(&_mutex, NULL);		// Never return error.
	pthread_cond_init(&_rcnd, NULL);		// Never return error.
	if (pthread_attr_init(&_tattr))
		perror("Error: Thread::Thread(): Initial attribute");
	if (pthread_attr_getschedpolicy(&_tattr, &_tpoli))
		perror("Error: Thread::Thread(): Get schedule policy");
	if (pthread_attr_getschedparam(&_tattr, &_tparm))
		perror("Error: Thread::Thread(): Get schedule parameter");
}

CThread::~CThread()
{
	pthread_cond_destroy(&_rcnd);
	pthread_mutex_destroy(&_mutex);
	pthread_attr_destroy(&_tattr);
}

/**
 * Create a thread to execute run().
 */
bool CThread::start()
{
	PINF_3("Starting the thread.");
	if (_tid == 0) {
		if (pthread_create(&_tid, &_tattr, thread_caller, this) != 0) {
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
bool CThread::join()
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
bool CThread::join(unsigned timeout)
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
bool CThread::cancel()
{
	if (pthread_cancel(_tid)) {
		PINF_3("Thread canceled.");
		return _canceled = true;
	}
	PERR("Failed to cancel thread.");
	return false;
}

/**
 * Get the minimum priority. Return -1 on error.
 */
int CThread::minimumPriority()
{
	int p;
	if ((p = sched_get_priority_min(_tpoli)) == -1)
		perror("Error: Thread::minimumPriority()");
	return p;
}

/**
 * Get the maximum priority. Return -1 on error.
 */
int CThread::maximumPriority()
{
	int p;
	if ((p = sched_get_priority_max(_tpoli)) == -1)
		perror("Error: Thread::maximumPriority()");
	return p;
}

/**
 * Get current priority setting. Return -1 on error.
 */
int CThread::priority()
{
	if (isRunning()) {
		if (pthread_getschedparam(_tid, &_tpoli, &_tparm)) {
			perror("Error: Thread::priority(): Get runtime priority");
			return -1;
		}
	} else {
		if (pthread_attr_getschedparam(&_tattr, &_tparm)) {
			perror("Error: Thread::priority(): Get attribute priority");
			return -1;
		}
	}
	return _tparm.sched_priority;
}

/**
 * Set the priority.
 *
 * \return True on success, false on error.
 */
bool CThread::setPriority(int p)
{
	_tparm.sched_priority = p;
	if (isRunning()) {
		if (pthread_setschedparam(_tid, _tpoli, &_tparm)) {
			perror("Error: Thread::setPriority(): Set runtime priority");
			return false;
		}
	} else {
		if (pthread_attr_setschedparam(&_tattr, &_tparm)) {
			perror("Error: Thread::setPriority(): Set attribute priority");
			return false;
		}
	}
	return true;
}

}
