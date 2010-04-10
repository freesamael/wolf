/*
 * RandomNumberGeneratorActor.h
 *
 *  Created on: Apr 9, 2010
 *      Author: samael
 */

#ifndef RANDOMNUMBERGENERATORACTOR_H_
#define RANDOMNUMBERGENERATORACTOR_H_

#include <ctime>
#include <cstdlib>
#include "AbstractManagerActor.h"

class RandomNumberGeneratorActor: public wfe::AbstractManagerActor
{
public:
	RandomNumberGeneratorActor();
	inline void prefire() { _state = RUNNING; }
	inline void postfire() { _state = FINISH; }
	inline void reset() { _state = NOT_READY; }
	void fire();
	State state();
};

#endif /* RANDOMNUMBERGENERATORACTOR_H_ */
