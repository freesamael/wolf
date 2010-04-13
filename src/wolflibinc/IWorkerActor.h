/**
 * \file IWorkerActor.h
 * \date Apr 13, 2010
 * \author samael
 */

#ifndef IWORKERACTOR_H_
#define IWORKERACTOR_H_

#include "IActor.h"

namespace wfe
{

class ManagerActor;
class IWorkerActor: public IActor
{
public:
	virtual ~IWorkerActor() {}
	virtual void initialize(ManagerActor *manager) = 0;
	virtual void finalize(ManagerActor *manager) = 0;
};

}

#endif /* IWORKERACTOR_H_ */
