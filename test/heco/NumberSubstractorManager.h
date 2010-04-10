/*
 * NumberSubstractorManager.h
 *
 *  Created on: Apr 9, 2010
 *      Author: samael
 */

#ifndef NUMBERSUBSTRACTORMANAGER_H_
#define NUMBERSUBSTRACTORMANAGER_H_

#include <AbstractManagerActor.h>
#include <SharedMemory.h>

class NumberSubstractorManager: public wfe::AbstractManagerActor
{
public:
	NumberSubstractorManager();
	void prefire();
	void fire() {}
	void postfire();
	inline void reset() { _state = NOT_READY; }
	State state();

private:
	cml::SharedMemory *_sm;
};

#endif /* NUMBERSUBSTRACTORMANAGER_H_ */
