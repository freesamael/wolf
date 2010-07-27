/**
 * \file HecoDSMFinalizer.h
 * \date Apr 15, 2010
 * \author samael
 */

#ifndef HECODSMFINALIZER_H_
#define HECODSMFINALIZER_H_

#include <AActor.h>

class HecoDSMFinalizer: public wolf::AActor
{
public:
	HecoDSMFinalizer(): _state(NOT_READY) { addPort(wolf::IPort::SINK); }
	State state();
	void fire();

private:
	State _state;
};

#endif /* HECODSMFINALIZER_H_ */
