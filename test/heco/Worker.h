/**
 * \file Worker.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef WORKER_H_
#define WORKER_H_

#include <AbstractWorkerActor.h>
#include <DUInt32.h>

class Worker: public wfe::AbstractWorkerActor
{
public:
	void managerInitialization(wfe::IManagerActor *mgr);
	void managerFinalization(wfe::IManagerActor *mgr);
	void managerPrefire(wfe::IManagerActor *mgr);
	void managerPostfire(wfe::IManagerActor *mgr);
	void fire();
	void setNum(wfe::DUInt32 n) { _n = n; }
	void update(const AbstractWorkerActor &o);
	cml::StandardTLVBlock* toTLVBlock() const;

private:
	wfe::DUInt32 _n;
};

#endif /* WORKER_H_ */
