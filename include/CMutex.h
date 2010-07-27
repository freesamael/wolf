/**
 * \file CMutex.h
 * \date Apr 27, 2010
 * \author samael
 */

#ifndef CMUTEX_H_
#define CMUTEX_H_

#include <pthread.h>
#include "XThread.h"
#include "HelperMacros.h"

namespace wolf
{

/**
 * CMutex represents a mutex object.
 */
class CMutex
{
	friend class CWaitCondition;
public:
	CMutex() throw(XThread);
	~CMutex() throw();
	void lock() throw(XThread);
	void unlock() throw(XThread);

private:
	CMutex(const CMutex &UNUSED(o)): _mutex() {}
	CMutex& operator=(const CMutex &UNUSED(o)) { return *this; }
	pthread_mutex_t _mutex;
};

}

#endif /* CMUTEX_H_ */
