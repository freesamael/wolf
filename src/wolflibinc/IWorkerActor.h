/**
 * \file IWorkerActor.h
 * \date Apr 13, 2010
 * \author samael
 */

#ifndef IWORKERACTOR_H_
#define IWORKERACTOR_H_

#include <ITLVObject.h>
#include "IActor.h"

namespace wfe
{

class ManagerActor;

/**
 * In addition to the methods IActor defined, IWorkerActor adds initialize()
 * to setup the ManagerActor it belongs to, and finalize() to wrap up the
 * ManagerActor. Note that the methods initialize() and finalize() are called
 * on the director host, and the whole execution, including setup, iteration
 * and wrapup phases happen on a runner host after the worker actor migrated
 * onto it. If a worker actor is going to be reset, it will happen on director
 * host.
 *
 * As a typical scenario, a worker actor might setup its manager within
 * initialize(), migrates to the runner, allocates DSM shared memory in setup(),
 * load the piece it needs in this iteration with prefire(), do the computation
 * in fire(), write back the partial results in postfire(), continue iterate
 * until all jobs are finished and use barrier to wait all workers in wrapup()
 * method. Afterward, it might use finalize() to write the result to output
 * ports attached on the manager.
 */
class IWorkerActor: public IActor, public cml::ITLVObject
{
public:
	virtual ~IWorkerActor() {}
	/// Setup the ManagerActor it belongs to.
	virtual void initialize(ManagerActor *manager) = 0;
	/// Wrap up the ManagerActor it belongs to.
	virtual void finalize(ManagerActor *manager) = 0;
};

}

#endif /* IWORKERACTOR_H_ */
