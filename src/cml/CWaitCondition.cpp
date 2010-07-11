/**
 * \file CWaitCondition.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <cstring>
#include <errno.h>
#include <sys/time.h>
#include "CWaitCondition.h"

using namespace std;

namespace cml
{

CWaitCondition::CWaitCondition() throw(XThread):
		_cond()
{
	int e;
	if ((e = pthread_cond_init(&_cond, NULL)) != 0)
		throw XThread(e);
}

CWaitCondition::~CWaitCondition() throw()
{
	int e;
	if ((e = pthread_cond_destroy(&_cond)) != 0)
		PERR(strerror(e));
}

/**
 * Unlock the mutex and wait for the condition. Always return true.
 */
bool CWaitCondition::wait(CMutex *mutex) throw(XThread)
{
	int e;
	if ((e = pthread_cond_wait(&_cond, &mutex->_mutex)) != 0)
		throw XThread(e);
	return true;
}

/**
 * Unlock the mutex and wait for the condition with given timeout time
 * (specified in microseconds).
 *
 * \return
 * True on success, false if timed out.
 */
bool CWaitCondition::wait(CMutex *mutex, unsigned timeout_us) throw(XThread)
{
	struct timeval now, abs_tout;
	struct timeval rel_tout = {timeout_us / 1000000L, timeout_us % 1000000L};
	struct timespec tout;

	// Set time.
	gettimeofday(&now, NULL);
	timeradd(&now, &rel_tout, &abs_tout);
	tout.tv_sec = abs_tout.tv_sec;
	tout.tv_nsec = abs_tout.tv_usec * 1000;

	int e;
	if ((e = pthread_cond_timedwait(&_cond, &mutex->_mutex, &tout)) != 0) {
		if (e == ETIMEDOUT) // timed out.
			return false;
		else
			throw XThread(e);
	}
	return true;
}

/**
 * Wake up one waiter.
 */
void CWaitCondition::wakeOne() throw(XThread)
{
	int e;
	if ((e = pthread_cond_signal(&_cond)) != 0)
		throw XThread(e);
}

/**
 * Wake up all waiters.
 */
void CWaitCondition::wakeAll() throw(XThread)
{
	int e;
	if ((e = pthread_cond_broadcast(&_cond)) != 0)
		throw XThread(e);
}

}
