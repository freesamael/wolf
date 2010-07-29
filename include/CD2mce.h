/**
 * \file CD2mce.h
 * \date Mar 17, 2010
 * \author samael
 */

#ifndef CD2MCE_H_
#define CD2MCE_H_

#include <iostream>
#include <string>
#include <vector>
#include "HelperMacros.h"
#include "CSharedMemory.h"

namespace wolf
{

#ifdef __D2MCE__ /* DSM mode */

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
#endif /* __D2MCE__ */

}

#endif /* CD2MCE_H_ */

