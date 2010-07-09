/**
 * \file HecoWorker.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef HECOWORKER_H_
#define HECOWORKER_H_

#include <AWorkerActor.h>
#include <CFlowUint32.h>

class HecoWorker: public wfe::AWorkerActor
{
public:
	void managerInitialization(wfe::IManagerActor *mgr);
	void managerFinalization(wfe::IManagerActor *mgr);
	void managerPrefire(wfe::IManagerActor *mgr);
	void managerPostfire(wfe::IManagerActor *mgr);
	void fire();
	void setNum(wfe::CFlowUint32 n) { _n = n; }
	void update(AWorkerActor *o);
	cml::CTlvBlock* toTLVBlock() const;

private:
	wfe::CFlowUint32 _n;
};

#endif /* HECOWORKER_H_ */
