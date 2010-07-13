/**
 * \file CMutex.cpp
 * \date Jul 11, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <cstring>
#include "CMutex.h"

using namespace std;

namespace cml
{

CMutex::CMutex() throw(XThread):
		_mutex()
{
	int e;
	if ((e = pthread_mutex_init(&_mutex, NULL)) != 0)
		throw XThread(__PRETTY_FUNCTION__, __LINE__, e);
}

CMutex::~CMutex() throw()
{
	int e;
	if ((e = pthread_mutex_destroy(&_mutex)) != 0)
		PERR(strerror(e));
}

/**
 * Lock the mutex.
 */
void CMutex::lock() throw(XThread)
{
	int e;
	if ((e = pthread_mutex_lock(&_mutex)) != 0)
		throw XThread(__PRETTY_FUNCTION__, __LINE__, e);
}

/**
 * Unlock the mutex.
 */
void CMutex::unlock() throw(XThread)
{
	int e;
	if ((e = pthread_mutex_unlock(&_mutex)) != 0)
		throw XThread(__PRETTY_FUNCTION__, __LINE__, e);
}

}
