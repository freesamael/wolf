/**
 * \file HecoWorker.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef HECOWORKER_H_
#define HECOWORKER_H_

#include <AbstractWorkerActor.h>
#include <DUInt32.h>

class HecoWorker: public wfe::AbstractWorkerActor
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

#endif /* HECOWORKER_H_ */
