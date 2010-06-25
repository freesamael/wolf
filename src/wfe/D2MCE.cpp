/**
 * \file D2MCE.cpp
 * \date Mar 17, 2010
 * \author samael
 */

#ifdef ENABLE_D2MCE /* DSM mode */
#include <cstdlib>
#include <cstring>
#include <sstream>
#include "SingletonAutoDestructor.h"
#include "D2MCE.h"
#include "SharedMemory.h"

using namespace std;

namespace wfe
{

SINGLETON_REGISTRATION(D2MCE);
SINGLETON_REGISTRATION_END();

D2MCE::D2MCE():
		SINGLETON_MEMBER_INITLST, _nodeid(0), _barrier(), _bufs(), _mutexes()
{
	PINF_3("Initializing d2mce.");
	d2mce_init();
}

D2MCE::~D2MCE()
{
	PINF_3("Finalizing d2mce.");
	for (unsigned i = 0; i < _mutexes.size(); i++)
		free(_mutexes[i]);
	d2mce_finalize();
	PINF_3("d2mce finalized.");
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
	PINF_3("Join d2mce computing group.");
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
	PINF_3("Barrier.");
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
 * Create a piece of shared memory with given size. If the name was not given,
 * it's decided by D2MCE automatically.
 */
SharedMemory* D2MCE::createSharedMemory(size_t size, const string &name)
{
	d2mce_mutex_t *mutex = (d2mce_mutex_t *)malloc(sizeof(d2mce_mutex_t));
	stringstream memname;
	stringstream mutexname;

	// Set name and mutex name.
	if (name.empty())
		memname << "m_" << _bufs.size();
	else
		memname << name;
	mutexname << memname.str() << "_mux";
	PINF_3("Creating shared memory with name = " << memname.str() <<
			", mutex name = " << mutexname.str() << ", and size = " << size);

	// Allocate memory and initialize mutex.
	memset(mutex, 0, sizeof(d2mce_mutex_t));
	d2mce_mutex_init(mutex, mutexname.str().c_str());
	_bufs.push_back((char *)d2mce_malloc(memname.str().c_str(), size));
	_mutexes.push_back(mutex);

	return new SharedMemory(memname.str(), _bufs.back(), size, _mutexes.back());
}

}

#endif /* ENABLE_D2MCE */
