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
#include <pthread.h>
#include <d2mce/d2mce.h>

namespace cml
{

class SharedMemory;
class D2MCE
{
public:
	static D2MCE *instance();
	static void release();
	bool join(std::string appname, std::string groupname = "default");
	bool barrier(unsigned int nnodes);
	SharedMemory* createSharedMemory(const std::string &name, size_t size);
	SharedMemory* findSharedMemory(const std::string &name);

private:
	D2MCE();
	~D2MCE();
	static D2MCE *_instance;
	static pthread_mutex_t _pthmutex;
	int _nodeid;
	d2mce_barrier_t _barrier;
	std::vector<SharedMemory*> _smems;
};

}

#endif /* D2MCE_H_ */
