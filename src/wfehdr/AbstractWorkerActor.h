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

namespace wfe
{

class ManagerActor;

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
 */
class AbstractWorkerActor: public AbstractActor, public cml::ITLVObject
{
public:
	virtual ~AbstractWorkerActor() {}
	virtual State state() { return READY; }
	virtual void managerInitialization(ManagerActor *UNUSED(manager)) {}
	virtual void managerFinalization(ManagerActor *UNUSED(manager)) {}
	virtual void managerPrefire(ManagerActor *UNUSED(manager)) {}
	virtual void managerPostfire(ManagerActor *UNUSED(manager)) {}
};

}

#endif /* ABSTRACTWORKERACTOR_H_ */
