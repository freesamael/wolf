/*
 * D2MCE.cpp
 *
 *  Created on: Mar 17, 2010
 *      Author: samael
 */

#include "D2MCE.h"
#include "SharedMemory.h"

using namespace std;

namespace cml
{

D2MCE *D2MCE::_instance = NULL;
pthread_mutex_t D2MCE::_pthmutex = PTHREAD_MUTEX_INITIALIZER;

D2MCE::D2MCE()
{
	d2mce_init();
}

D2MCE::~D2MCE()
{
	for (int i = 0; i < (int)_smems.size(); i++)
		delete _smems[i];
	d2mce_finalize();
}

D2MCE* D2MCE::instance()
{
	pthread_mutex_lock(&_pthmutex);
	if (_instance == NULL)
		_instance = new D2MCE();
	pthread_mutex_unlock(&_pthmutex);
	return _instance;
}

void D2MCE::release()
{
	pthread_mutex_lock(&_pthmutex);
	delete _instance;
	_instance = NULL;
	pthread_mutex_unlock(&_pthmutex);
}

/**
 * @brief Join a D2MCE computing group.
 * @return True on success, false otherwise.
 */
bool D2MCE::join(string appname, string groupname)
{
	_nodeid = d2mce_join(appname.c_str(), groupname.c_str(), D2MCE_GROUP_ANY);
	return (d2mce_barrier_init(&_barrier, "barrier") == 1 && _nodeid > 0);
}

/**
 * @brief Barrier.
 * @param nnodes Number of nodes to wait (including the calling node itself).
 * @return True on success, false otherwise.
 */
bool D2MCE::barrier(unsigned int nnodes)
{
	return (d2mce_barrier(&_barrier, nnodes) == 1);
}

/**
 * @brief Create a piece of shared memory with given size and name.
 * @note D2MCE takes the ownership of shared memory and will delete/free the memory.
 */
SharedMemory* D2MCE::createSharedMemory(const string &name, size_t size)
{
	SharedMemory *mem = new SharedMemory(name, size);
	_smems.push_back(mem);
	return mem;
}

/**
 * @brief Find a piece of shared memory with given name.
 * @return Proper shared memory, or NULL if not found.
 */
SharedMemory* D2MCE::findSharedMemory(const string &name)
{
	for (int i = 0; i < (int)_smems.size(); i++)
		if (_smems[i]->name() == name)
			return _smems[i];
	return NULL;
}

}
