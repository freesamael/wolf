/**
 * \file CMutex.h
 * \date Apr 27, 2010
 * \author samael
 */

#ifndef CMUTEX_H_
#define CMUTEX_H_

#include <pthread.h>
#include "HelperMacros.h"

namespace cml
{

/**
 * Mutex is generated to unlock on destruction.
 */
class CMutex
{
	friend class CWaitCondition;
public:
	CMutex(): _mutex() { pthread_mutex_init(&_mutex, NULL); }
	~CMutex() { pthread_mutex_destroy(&_mutex); }
	/// Lock the mutex. Return true if successed.
	inline bool lock() { return !(pthread_mutex_lock(&_mutex)); }
	/// Unlock the mutex. Return true if successed.
	inline bool unlock() { return !(pthread_mutex_unlock(&_mutex)); }

private:
	CMutex(const CMutex &UNUSED(o)): _mutex() {}
	CMutex& operator=(const CMutex &UNUSED(o)) { return *this; }
	pthread_mutex_t _mutex;
};

}

#endif /* CMUTEX_H_ */
