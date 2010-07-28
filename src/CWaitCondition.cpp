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

CWaitCondition::CWaitCondition() :
		_cond()
{
	int e;
	if ((e = pthread_cond_init(&_cond, NULL)) != 0)
		throw XThread(e);
}

CWaitCondition::~CWaitCondition() 
{
	int e;
	if ((e = pthread_cond_destroy(&_cond)) != 0)
		PERR(strerror(e));
}

/**
 * Unlock the mutex and wait for the condition. Always return true.
 */
bool CWaitCondition::wait(CMutex *mutex) 
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
bool CWaitCondition::wait(CMutex *mutex, unsigned timeout_us) 
{
	struct timespec timeout = (CTime::now() + CTime(timeout_us)).toTimespec();

	int e;
	if ((e = pthread_cond_timedwait(&_cond, &mutex->_mutex, &timeout)) != 0) {
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
void CWaitCondition::wakeOne() 
{
	int e;
	if ((e = pthread_cond_signal(&_cond)) != 0)
		throw XThread(e);
}

/**
 * Wake up all waiters.
 */
void CWaitCondition::wakeAll() 
{
	int e;
	if ((e = pthread_cond_broadcast(&_cond)) != 0)
		throw XThread(e);
}

}
