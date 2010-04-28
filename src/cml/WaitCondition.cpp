/**
 * \file WaitCondition.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include <sys/time.h>
#include <cstdio>
#include <errno.h>
#include "WaitCondition.h"

namespace cml
{

WaitCondition::WaitCondition():
		_cond()
{
	pthread_cond_init(&_cond, NULL);
}

WaitCondition::~WaitCondition()
{
	if (pthread_cond_destroy(&_cond))
		perror("Error: WaitCondition::~WaitCondition()");
}

/**
 * Wait the condition. Return true on success (though pthread_cond_wait never
 * returns error).
 */
bool WaitCondition::wait(Mutex *mutex)
{
	return !pthread_cond_wait(&_cond, &mutex->_mutex);
}

/**
 * Wait the condition with given timeout time (specified in microseconds).
 *
 * \return
 * True on success.
 */
bool WaitCondition::wait(Mutex *mutex, unsigned timeout)
{
	struct timeval now, abs_tout;
	struct timeval rel_tout = {timeout / 1000000, timeout % 1000000};
	struct timespec tout;

	// Set time.
	gettimeofday(&now, NULL);
	timeradd(&now, &rel_tout, &abs_tout);
	tout.tv_sec = abs_tout.tv_sec;
	tout.tv_nsec = abs_tout.tv_usec * 1000;

	if (pthread_cond_timedwait(&_cond, &mutex->_mutex, &tout) == 0) {
		perror("Error: WaitCondition::wait()");
		return false;
	}
	return true;
}

/**
 * Wake up one waiter.
 */
void WaitCondition::wakeOne()
{
	pthread_cond_signal(&_cond);
}

/**
 * Wake up all waiters.
 */
void WaitCondition::wakeAll()
{
	pthread_cond_broadcast(&_cond);
}

}