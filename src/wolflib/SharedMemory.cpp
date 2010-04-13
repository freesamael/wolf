/**
 * \file SharedMemory.cpp
 * \date Mar 18, 2010
 * \author samael
 */

#include <cstring>
#include "SharedMemory.h"
#include "D2MCE.h"

using namespace std;

namespace wfe
{

/**
 * Allocate a piece of shared memory on DSM.
 */
SharedMemory::SharedMemory(string name, size_t size):
		_name(name), _size(size)
{
	d2mce_mutex_init(&_mutex, (name + "_mutex").c_str());
	_buf = (char *)d2mce_malloc(name.c_str(), size);
}

/**
 * Clone the shared memory. It's done by D2MCE::createSharedMemory().
 */
IDrop* SharedMemory::clone() const
{
	SharedMemory *sm = D2MCE::instance()->createSharedMemory(_name, _size);
	memcpy(sm->buffer(), _buf, _size);
	return sm;
}

}
