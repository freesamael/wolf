/*
 * D2MCE.h
 *
 *  Created on: Mar 17, 2010
 *      Author: samael
 */

#ifndef D2MCE_H_
#define D2MCE_H_

#include <string>
#include <vector>
#include <d2mce/d2mce.h>
#include "SharedMemory.h"

namespace cml
{

/**
 * Wrapper for D2MCE.
 */
class D2MCE
{
public:
	static D2MCE *instance();
	static void release();
	bool join(std::string appname, std::string groupname = "default");
	bool barrier(unsigned int nnodes);
	int nodeId() const { return _nodeid; }
	int getNumberOfNodes() const;
	SharedMemory* createSharedMemory(const std::string &name, size_t size);
	SharedMemory* findSharedMemory(const std::string &name);

private:
	D2MCE();
	~D2MCE();
	static D2MCE *_instance;
	int _nodeid;
	d2mce_barrier_t _barrier;
	std::vector<SharedMemory*> _smems;
};

}

#endif /* D2MCE_H_ */
