/**
 * \file D2MCE.h
 * \date Mar 17, 2010
 * \author samael
 */

#ifndef D2MCE_H_
#define D2MCE_H_

#include <iostream>
#include <string>
#include <vector>
#include "HelperMacros.h"
#include "SharedMemory.h"

namespace wfe
{

#ifndef DISABLE_D2MCE

#include <d2mce/d2mce.h>
/**
 * A wrapper for D2MCE.
 */
class D2MCE
{
	SINGLETON(D2MCE);
public:
	bool join(std::string appname, std::string groupname = "default");
	bool barrier(unsigned int nnodes);
	int nodeId() const { return _nodeid; }
	int getNumberOfNodes() const;
	SharedMemory* createSharedMemory(size_t size, const std::string &name = "");

private:
	D2MCE();
	~D2MCE();
	int _nodeid;
	d2mce_barrier_t _barrier;
	std::vector<char*> _bufs;
	std::vector<d2mce_mutex_t*> _mutexes;
};

#else
#endif /* DISABLE_D2MCE */

}

#endif /* D2MCE_H_ */

