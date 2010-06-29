/**
 * \file AbstractWorkerActor.h
 * \date Apr 13, 2010
 * \author samael
 */

#ifndef ABSTRACTWORKERACTOR_H_
#define ABSTRACTWORKERACTOR_H_

#include "ITLVObject.h"
#include "HelperMacros.h"
#include "AbstractActor.h"
#include "IManagerActor.h"

namespace wfe
{

/**
 * In addition to the methods AbstractActor defined, AbstractWorkerActor adds
 * initialize() to setup the ManagerActor it belongs to, and finalize() to wrap
 * up the ManagerActor. Note that the methods initialize() and finalize() are
 * called on the master host, and the execution, including setup, iteration
 * and wrapup phases happen on a runner host after the worker actor migrated
 * onto it. If a worker actor is going to be reset, it will be done on the
 * master host.
 *
 * As a typical scenario, a worker actor might setup its manager within
 * initialize(), migrates to the runner, allocates DSM shared memory in setup(),
 * load the piece it needs in this iteration with prefire(), do the computation
 * in fire(), write back the partial results in postfire(), continue iterate
 * until all jobs are finished and use barrier to wait all workers in wrapup()
 * method. Afterward, it might use finalize() to write the result to output
 * ports attached on the manager.
 *
 * \note A worker must has valid assignment operator. Manager uses assignment
 * to update the value of original worker when the sent worker migrated back.
 */
class AbstractWorkerActor: public AbstractActor, public cml::ITLVObject
{
public:
	virtual ~AbstractWorkerActor() {}
	/// In usual case, worker actor is always ready.
	virtual State state() { return READY; }
	/// Initialize manager. Called on construction of manager.
	virtual void managerInitialization(IManagerActor *UNUSED(mgr)) {}
	/// Finalize manager. Called on destruction of manager.
	virtual void managerFinalization(IManagerActor *UNUSED(mgr)) {}
	/// Prefire manager. Called on ManagerActor::prefire().
	virtual void managerPrefire(IManagerActor *UNUSED(mgr)) {}
	/// Postfire manager. Called on ManagerActor::postfire().
	virtual void managerPostfire(IManagerActor *UNUSED(mgr)) {}
	/// When a worker returns from runner, manager uses this function to update
	/// the value of original worker.
	virtual void update(AbstractWorkerActor *o) = 0;
};

}

#endif /* ABSTRACTWORKERACTOR_H_ */
