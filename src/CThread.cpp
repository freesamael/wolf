/**
 * \file CThread.cpp
 * \date Mar 9, 2010
 * \author samael
 */

#include "CThread.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <errno.h>
#include "HelperMacros.h"

using namespace std;

namespace wolf
{

/**
 * \internal
 * A thread function adaptor.
 */
void* thread_caller(void *param)
{
	wolf::CThread *th = reinterpret_cast<wolf::CThread *>(param);

	th->_mutex.lock();
	th->_running = true;
	th->_mutex.unlock();

	th->run();

	th->_mutex.lock();
	th->_running = false;
	th->_finished = true;
	th->_mutex.unlock();

	th->_cond.wakeAll();
	return NULL;
}

CThread::CThread(IRunnable *runner) :
		_runner(runner), _mutex(), _cond(),	_tid(0), _tattr(), _tpoli(0),
		_tparm(), _running(false), _finished(false), _canceled(false)
{
	int e;
	if ((e = pthread_attr_init(&_tattr)) != 0)
		throw XThread(e);
	if ((e = pthread_attr_getschedpolicy(&_tattr, &_tpoli)) != 0)
		throw XThread(e);
	if ((e = pthread_attr_getschedparam(&_tattr, &_tparm)) != 0)
		throw XThread(e);
}

CThread::~CThread()
{
	int e;
	if ((e = pthread_attr_destroy(&_tattr)) != 0)
		PERR(strerror(e));
}

/**
 * Create a thread to execute run().
 */
void CThread::start()
{
	if (_tid != 0)
		throw XThread(XThread::THREAD_ALREADY_STARTED);

	int e;
	if ((e = pthread_create(&_tid, &_tattr, thread_caller, this)) != 0)
		throw XThread(e);
}

/**
 * Block wait until thread exits. Always return true.
 */
bool CThread::join()
{
	int e;
	if ((e = pthread_join(_tid, NULL)) != 0)
		throw XThread(e);
	return true;
}

/**
 * Block wait until thread exits or timeout.
 *
 * \param timeout_us
 * Timeout in microseconds.
 *
 * \return
 * True on success, false if timed out.
 */
bool CThread::join(unsigned timeout_us)
{
	_mutex.lock();
	if (_running)
		_cond.wait(&_mutex, timeout_us);
	_mutex.unlock();

	return true;
}

/**
 * Request cancel for executing thread.
 */
void CThread::cancel()
{
	int e;
	if ((e = pthread_cancel(_tid)) != 0)
		throw XThread(e);
	_canceled = true;
}

/**
 * Get the minimum priority.
 */
int CThread::minimumPriority()
{
	int p;
	if ((p = sched_get_priority_min(_tpoli)) == -1)
		throw XThread(errno);
	return p;
}

/**
 * Get the maximum priority.
 */
int CThread::maximumPriority()
{
	int p;
	if ((p = sched_get_priority_max(_tpoli)) == -1)
		throw XThread(errno);
	return p;
}

/**
 * Get current priority setting.
 */
int CThread::priority()
{
	if (isRunning()) {
		int e;
		if ((e = pthread_getschedparam(_tid, &_tpoli, &_tparm)) != 0)
			throw XThread(e);
	} else {
		int e;
		if ((e = pthread_attr_getschedparam(&_tattr, &_tparm)) != 0)
			throw XThread(e);
	}
	return _tparm.sched_priority;
}

/**
 * Set the priority.
 */
void CThread::setPriority(int p)
{
	_tparm.sched_priority = p;
	if (isRunning()) {
		int e;
		if ((e = pthread_setschedparam(_tid, _tpoli, &_tparm)) != 0)
			throw XThread(e);
	} else {
		int e;
		if ((e = pthread_attr_setschedparam(&_tattr, &_tparm)) != 0)
			throw XThread(e);
	}
}

}
