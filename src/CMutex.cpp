/**
 * \file CMutex.cpp
 * \date Jul 11, 2010
 * \author samael
 */

#include "CMutex.h"

#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

namespace wolf
{

CMutex::CMutex() :
		_mutex()
{
	int e;
	if ((e = pthread_mutex_init(&_mutex, NULL)) != 0)
		throw XThread(e);
}

CMutex::~CMutex()
{
	int e;
	if ((e = pthread_mutex_destroy(&_mutex)) != 0)
		PERR(strerror(e));
}

/**
 * Lock the mutex.
 */
void CMutex::lock()
{
	int e;
	if ((e = pthread_mutex_lock(&_mutex)) != 0)
		throw XThread(e);
}

/**
 * Unlock the mutex.
 */
void CMutex::unlock()
{
	int e;
	if ((e = pthread_mutex_unlock(&_mutex)) != 0)
		throw XThread(e);
}

}
