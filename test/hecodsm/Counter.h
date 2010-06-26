/**
 * \file Counter.h
 * \date Apr 15, 2010
 * \author samael
 */

#ifndef COUNTER_H_
#define COUNTER_H_

#include <HelperMacros.h>
#include <SharedMemory.h>
#include <TLVSharedMemoryInfo.h>
#include <AbstractWorkerActor.h>

class Counter: public wfe::AbstractWorkerActor
{
public:
	Counter();
	~Counter();
	void managerInitialization(wfe::IManagerActor *mgr);
	void managerFinalization(wfe::IManagerActor *mgr);
	void managerPrefire(wfe::IManagerActor *mgr);
	void managerPostfire(wfe::IManagerActor *mgr);
	void setup();
	void fire();
	void postfire();
	void update(const AbstractWorkerActor &UNUSED(o)) {}
	cml::StandardTLVBlock* toTLVBlock() const;
	void setMeminfo(wfe::TLVSharedMemoryInfo *meminfo) { _meminfo = meminfo; }

private:
	wfe::SharedMemory *_mem;
	wfe::TLVSharedMemoryInfo *_meminfo;
};

#endif /* COUNTER_H_ */
