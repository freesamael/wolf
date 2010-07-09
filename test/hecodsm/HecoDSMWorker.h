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

class HecoDSMWorker: public wfe::AWorkerActor
{
public:
	HecoDSMWorker();
	~HecoDSMWorker();
	void managerInitialization(wfe::IManagerActor *mgr);
	void managerFinalization(wfe::IManagerActor *mgr);
	void managerPrefire(wfe::IManagerActor *mgr);
	void managerPostfire(wfe::IManagerActor *mgr);
	void setup();
	void fire();
	void postfire();
	void update(AWorkerActor *UNUSED(o)) {}
	cml::CTlvBlock* toTLVBlock() const;
	void setMeminfo(wfe::CTlvSharedMemoryInfo *meminfo) { _meminfo = meminfo; }

private:
	wfe::SharedMemory *_mem;
	wfe::CTlvSharedMemoryInfo *_meminfo;
};

#endif /* HECODSMWORKER_H_ */
