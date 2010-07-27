/**
 * \file HecoDSMWorker.h
 * \date Apr 15, 2010
 * \author samael
 */

#ifndef HECODSMWORKER_H_
#define HECODSMWORKER_H_

#include <HelperMacros.h>
#include <CSharedMemory.h>
#include <CTlvSharedMemoryInfo.h>
#include <AWorkerActor.h>

class HecoDSMWorker: public wolf::AWorkerActor
{
public:
	HecoDSMWorker();
	~HecoDSMWorker();
	void managerInitialization(wolf::IManagerActor *mgr);
	void managerFinalization(wolf::IManagerActor *mgr);
	void managerPrefire(wolf::IManagerActor *mgr);
	void managerPostfire(wolf::IManagerActor *mgr);
	void setup();
	void fire();
	void postfire();
	void update(AWorkerActor *UNUSED(o)) {}
	wolf::CTlvBlock* toTLVBlock() const;
	void setMeminfo(wolf::CTlvSharedMemoryInfo *meminfo) { _meminfo = meminfo; }

private:
	wolf::SharedMemory *_mem;
	wolf::CTlvSharedMemoryInfo *_meminfo;
};

#endif /* HECODSMWORKER_H_ */
