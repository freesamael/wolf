/**
 * \file NumberGenerator.h
 * \date Apr 15, 2010
 * \author samael
 */

#ifndef NUMBERGENERATOR_H_
#define NUMBERGENERATOR_H_

#include <AbstractActor.h>
#include <SharedMemory.h>
#include <IDrop.h>

class NumberGenerator: public wfe::AbstractActor
{
public:
	NumberGenerator(): _state(READY) { addPort(wfe::IPort::SOURCE); }
	~NumberGenerator() { delete sourcePorts()[0]; }
	State state() { return _state; }
	void prefire();
	void fire();
	void postfire();

private:
	wfe::SharedMemory *_item;
	State _state;
};

#endif /* NUMBERGENERATOR_H_ */
