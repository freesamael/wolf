/*
 * NumberReaderActor.h
 *
 *  Created on: Apr 9, 2010
 *      Author: samael
 */

#ifndef NUMBERREADERACTOR_H_
#define NUMBERREADERACTOR_H_

#include <AbstractManagerActor.h>

class NumberReaderActor: public wfe::AbstractManagerActor
{
public:
	NumberReaderActor() { _inports.push_back(new wfe::Port(this)); }
	inline void prefire() { _state = RUNNING; }
	inline void postfire() { _state = FINISH; }
	inline void reset() { _state = NOT_READY; }
	void fire();
	State state();
};

#endif /* NUMBERREADERACTOR_H_ */
