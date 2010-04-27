/**
 * \file SharedMemory.cpp
 * \date Mar 18, 2010
 * \author samael
 */

#ifndef DISABLE_D2MCE
#include <cstring>
#include "SharedMemory.h"
#include "D2MCE.h"

using namespace std;

namespace wfe
{

/**
 * Operator =
 */
SharedMemory& SharedMemory::operator=(const SharedMemory &sm)
{
	_name = sm._name;
	_buf = sm._buf;
	_size = sm._size;
	_mutex = sm._mutex;
	return *this;
}

/**
 * Clone the shared memory. It's done by D2MCE::createSharedMemory().
 */
IDrop* SharedMemory::clone() const
{
	return new SharedMemory(*this);
}

}

#endif /* DISABLE_D2MCE */
