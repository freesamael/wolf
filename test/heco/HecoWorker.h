/**
 * \file HecoWorker.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef HECOWORKER_H_
#define HECOWORKER_H_

#include <AWorkerActor.h>
#include <CFlowUint32.h>

class HecoWorker: public wolf::AWorkerActor
{
public:
	void managerInitialization(wolf::IManagerActor *mgr);
	void managerFinalization(wolf::IManagerActor *mgr);
	void managerPrefire(wolf::IManagerActor *mgr);
	void managerPostfire(wolf::IManagerActor *mgr);
	void fire();
	void setNum(wolf::CFlowUint32 n) { _n = n; }
	void update(AWorkerActor *o);
	wolf::CTlvBlock* toTLVBlock() const;

private:
	wolf::CFlowUint32 _n;
};

#endif /* HECOWORKER_H_ */
