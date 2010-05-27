/**
 * \file ActorExecutor.h
 * \date May 26, 2010
 * \author samael
 */

#ifndef ACTOREXECUTOR_H_
#define ACTOREXECUTOR_H_

#include <IRunnable.h>
#include "Runner.h"

namespace wfe
{

/**
 * Used by runner to execute actors.
 */
class ActorExecutor: public cml::IRunnable
{
public:
	ActorExecutor(Runner *parent): _parent(parent) {}
	ActorExecutor(const ActorExecutor &o): _parent(o._parent) {}
	ActorExecutor& operator=(const ActorExecutor &o)
		{ _parent = o._parent; return *this; }
	void run();

private:
	Runner* _parent;
};

}

#endif /* ACTOREXECUTOR_H_ */
