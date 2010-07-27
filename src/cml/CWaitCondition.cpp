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
#include "CTime.h"

using namespace std;

namespace wolf
{

CWaitCondition::CWaitCondition() throw(XThread):
		_cond()
{
	int e;
	if ((e = pthread_cond_init(&_cond, NULL)) != 0)
		throw XThread(__PRETTY_FUNCTION__, __LINE__, e);
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
		throw XThread(__PRETTY_FUNCTION__, __LINE__, e);
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
	struct timespec timeout = (CTime::now() + CTime(timeout_us)).toTimespec();

	int e;
	if ((e = pthread_cond_timedwait(&_cond, &mutex->_mutex, &timeout)) != 0) {
		if (e == ETIMEDOUT) // timed out.
			return false;
		else
			throw XThread(__PRETTY_FUNCTION__, __LINE__, e);
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
		throw XThread(__PRETTY_FUNCTION__, __LINE__, e);
}

/**
 * Wake up all waiters.
 */
void CWaitCondition::wakeAll() throw(XThread)
{
	int e;
	if ((e = pthread_cond_broadcast(&_cond)) != 0)
		throw XThread(__PRETTY_FUNCTION__, __LINE__, e);
}

}
