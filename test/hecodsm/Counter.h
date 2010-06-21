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
	void managerInitialization(wfe::ManagerActor *manager);
	void managerFinalization(wfe::ManagerActor *manager);
	void managerPrefire(wfe::ManagerActor *manager);
	void managerPostfire(wfe::ManagerActor *manager);
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
