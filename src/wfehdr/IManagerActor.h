/**
 * \file IManagerActor.h
 * \date Jun 26, 2010
 * \author samael
 */

#ifndef IMANAGERACTOR_H_
#define IMANAGERACTOR_H_

namespace wfe
{

class AWorkerActor;

/**
 * \interface IManagerActor
 * It defines the interface that all manager actors should implement.
 */
class IManagerActor
{
public:
	virtual ~IManagerActor() {}
	/// Called by Master to notify that a previous sent work has finished its
	/// job and returned.
	virtual void workerFinished(AWorkerActor *worker) = 0;
};

}

#endif /* IMANAGERACTOR_H_ */
