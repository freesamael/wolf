/**
 * \file D2MCE.h
 * \date Mar 17, 2010
 * \author samael
 */

#ifndef D2MCE_H_
#define D2MCE_H_

#include <string>
#include <vector>
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

#else

/**
 * A dummy d2mce class used to make compiler happy.
 */
class D2MCE
{
public:
	inline static D2MCE *instance() { return NULL; }
	inline static void release() {}
	inline bool join(std::string appname, std::string groupname = "default") {
		return false; }
	inline bool barrier(unsigned int nnodes) { return false; }
	inline int nodeId() const { return 0; }
	inline int getNumberOfNodes() const { return 0; }
	inline SharedMemory* createSharedMemory(const std::string &name,
		size_t size) { return NULL; }
	inline SharedMemory* findSharedMemory(const std::string &name) {
		return NULL; }

private:
	D2MCE() {}
};

#endif /* DISABLE_D2MCE */

}

#endif /* D2MCE_H_ */

