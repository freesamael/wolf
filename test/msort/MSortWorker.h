/**
 * \file MSortWorker.h
 * \date Jun 28, 2010
 * \author samael
 */

#ifndef MSORTWORKER_H_
#define MSORTWORKER_H_

#include <AbstractWorkerActor.h>
#include <DVector.h>

class MSortWorker: public wfe::AbstractWorkerActor
{
public:
	MSortWorker();
	void managerInitialization(wfe::IManagerActor *mgr);
	void managerFinalization(wfe::IManagerActor *mgr);
	void managerPrefire(wfe::IManagerActor *mgr);
	void managerPostfire(wfe::IManagerActor *mgr);
	void update(const AbstractWorkerActor &o);
	void fire();
	void setVector(const wfe::DVector<uint32_t> &v);
	cml::StandardTLVBlock* toTLVBlock() const;

private:
	wfe::DVector<uint32_t> _vec;
};

#endif /* MSORTWORKER_H_ */
