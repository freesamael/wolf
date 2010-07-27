/**
 * \file MSortWorker.h
 * \date Jun 28, 2010
 * \author samael
 */

#ifndef MSORTWORKER_H_
#define MSORTWORKER_H_

#include <AWorkerActor.h>
#include <CFlowVector.h>
#include <CMutex.h>

class MSortWorker: public wolf::AWorkerActor
{
public:
	MSortWorker();
	void managerInitialization(wolf::IManagerActor *mgr);
	void managerFinalization(wolf::IManagerActor *mgr);
	void managerPrefire(wolf::IManagerActor *mgr);
	void managerPostfire(wolf::IManagerActor *mgr);
	void update(AWorkerActor *o);
	void fire();
	wolf::CFlowVector<uint32_t> vector() const { return _vec; }
	void setVector(const wolf::CFlowVector<uint32_t> &v);
	wolf::CTlvBlock* toTLVBlock() const;

private:
	wolf::CFlowVector<uint32_t> _vec;
	wolf::CMutex _mx;
};

#endif /* MSORTWORKER_H_ */
