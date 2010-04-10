/*
 * NumberSubstractorWorker.h
 *
 *  Created on: Apr 9, 2010
 *      Author: samael
 */

#ifndef NUMBERSUBSTRACTORWORKER_H_
#define NUMBERSUBSTRACTORWORKER_H_

#include <AbstractWorkerActor.h>
#include <TLVSharedMemoryInfo.h>
#include <SharedMemory.h>

class NumberSubstractorWorker: public wfe::AbstractWorkerActor
{
public:
	NumberSubstractorWorker(wfe::TLVSharedMemoryInfo *sminfo = NULL):
			_sminfo(sminfo) {}
	~NumberSubstractorWorker() { delete _sminfo; }
	bool firecond() const { return (_firecount < 500); }
	void prefire();
	void fire();
	void postfire();
	inline void reset() {}
	inline State state() { return READY; }
	inline void setSMInfo(wfe::TLVSharedMemoryInfo *sminfo)
			{ _sminfo = sminfo; }
	cml::StandardTLVBlock* toTLVBlock() const;

private:
	wfe::TLVSharedMemoryInfo *_sminfo;
	cml::SharedMemory *_sm;
	int _firecount;
};

#endif /* NUMBERSUBSTRACTORWORKER_H_ */
