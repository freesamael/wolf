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

class MSortWorker: public wfe::AWorkerActor
{
public:
	MSortWorker();
	void managerInitialization(wfe::IManagerActor *mgr);
	void managerFinalization(wfe::IManagerActor *mgr);
	void managerPrefire(wfe::IManagerActor *mgr);
	void managerPostfire(wfe::IManagerActor *mgr);
	void update(AWorkerActor *o);
	void fire();
	wfe::CFlowVector<uint32_t> vector() const { return _vec; }
	void setVector(const wfe::CFlowVector<uint32_t> &v);
	cml::CTlvBlock* toTLVBlock() const;

private:
	wfe::CFlowVector<uint32_t> _vec;
	cml::CMutex _mx;
};

#endif /* MSORTWORKER_H_ */
