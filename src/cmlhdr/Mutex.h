/**
 * \file Mutex.h
 * \date Apr 27, 2010
 * \author samael
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

namespace cml
{

/**
 * Mutex is generated to unlock on destruction.
 */
class Mutex
{
	friend class WaitCondition;
public:
	Mutex(): _mutex() { pthread_mutex_init(&_mutex, NULL); }
	~Mutex() { pthread_mutex_destroy(&_mutex); }
	/// Lock the mutex. Return true if successed.
	inline bool lock() { return !(pthread_mutex_lock(&_mutex)); }
	/// Unlock the mutex. Return true if successed.
	inline bool unlock() { return !(pthread_mutex_unlock(&_mutex)); }

private:
	pthread_mutex_t _mutex;
};

}

#endif /* MUTEX_H_ */
