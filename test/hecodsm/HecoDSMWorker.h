/**
 * \file HecoDSMWorker.h
 * \date Apr 15, 2010
 * \author samael
 */

#ifndef HECODSMWORKER_H_
#define HECODSMWORKER_H_

#include <HelperMacros.h>
#include <SharedMemory.h>
#include <TLVSharedMemoryInfo.h>
#include <AbstractWorkerActor.h>

class HecoDSMWorker: public wfe::AbstractWorkerActor
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
	void update(AbstractWorkerActor *UNUSED(o)) {}
	cml::StandardTLVBlock* toTLVBlock() const;
	void setMeminfo(wfe::TLVSharedMemoryInfo *meminfo) { _meminfo = meminfo; }

private:
	wfe::SharedMemory *_mem;
	wfe::TLVSharedMemoryInfo *_meminfo;
};

#endif /* HECODSMWORKER_H_ */
