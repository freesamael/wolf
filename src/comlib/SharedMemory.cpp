/*
 * SharedMemory.cpp
 *
 *  Created on: Mar 18, 2010
 *      Author: samael
 */

#include "SharedMemory.h"

using namespace std;

namespace cml
{

SharedMemory::SharedMemory(string name, size_t size):
		_name(name), _size(size)
{
	d2mce_mutex_init(&_mutex, (name + "_mutex").c_str());
	_buf = (char *)d2mce_malloc(name.c_str(), size);
}

SharedMemory::~SharedMemory()
{
	// TODO Auto-generated destructor stub
}

}
