/**
 * \file D2MCE.cpp
 * \date Mar 17, 2010
 * \author samael
 */

#include <SingletonAutoDestructor.h>
#include <HelperMacros.h>
#include "D2MCE.h"
#include "SharedMemory.h"

using namespace std;

namespace wfe
{

SINGLETON_REGISTRATION(D2MCE);

D2MCE *D2MCE::_instance = NULL;

D2MCE::D2MCE()
{
	PINFO("Initialing d2mce.");
	d2mce_init();
}

D2MCE::~D2MCE()
{
	PINFO("Finalizing d2mce.");
	for (int i = 0; i < (int)_smems.size(); i++)
		delete _smems[i];
	d2mce_finalize();
}

D2MCE* D2MCE::instance()
{
	if (_instance == NULL)
		_instance = new D2MCE();
	return _instance;
}

void D2MCE::release()
{
	delete _instance;
	_instance = NULL;
}

/**
 * Join a D2MCE computing group.
 *
 * \return
 * True on success, false otherwise.
 *
 * \todo
 * Check the return value, it seems the value is always false.
 */
bool D2MCE::join(string appname, string groupname)
{
	PINFO("Join d2mce computing group.");
	_nodeid = d2mce_join(appname.c_str(), groupname.c_str(), D2MCE_GROUP_ANY);
	return (d2mce_barrier_init(&_barrier, "barrier") > 0 && _nodeid > 0);
}

/**
 * Barrier.
 *
 * \param nnodes
 * Number of nodes to wait (including the calling node itself).
 *
 * \return
 * True on success, false otherwise.
 */
bool D2MCE::barrier(unsigned int nnodes)
{
	PINFO("Barrier.");
	return (d2mce_barrier(&_barrier, nnodes) == 1);
}

/**
 * Get the number of nodes in current working group.
 */
int D2MCE::getNumberOfNodes() const
{
	return d2mce_getNodeNum();
}

/**
 * Create a piece of shared memory with given size and name.
 *
 * \note
 * D2MCE takes the ownership of shared memory and will delete/free the memory.
 */
SharedMemory* D2MCE::createSharedMemory(const string &name, size_t size)
{
	PINFO("Creating a shared memory.");
	SharedMemory *mem = new SharedMemory(name, size);
	_smems.push_back(mem);
	return mem;
}

/**
 * Find a piece of shared memory with given name.
 *
 * \return
 * Proper shared memory, or NULL if not found.
 */
SharedMemory* D2MCE::findSharedMemory(const string &name)
{
	for (int i = 0; i < (int)_smems.size(); i++)
		if (_smems[i]->name() == name)
			return _smems[i];
	return NULL;
}

}
