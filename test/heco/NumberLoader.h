/**
 * \file NumberLoader.h
 * \date Apr 15, 2010
 * \author samael
 */

#ifndef NUMBERLOADER_H_
#define NUMBERLOADER_H_

#include <AbstractActor.h>

class NumberLoader: public wfe::AbstractActor
{
public:
	NumberLoader(): _state(NOT_READY) { addPort(wfe::IPort::SINK); }
	State state();
	void fire();

private:
	State _state;
};

#endif /* NUMBERLOADER_H_ */
