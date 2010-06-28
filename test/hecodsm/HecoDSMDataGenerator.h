/**
 * \file HecoDSMDataGenerator.h
 * \date Apr 15, 2010
 * \author samael
 */

#ifndef HECODSMDATAGENERATOR_H_
#define HECODSMDATAGENERATOR_H_

#include <AbstractActor.h>
#include <SharedMemory.h>
#include <IDrop.h>

class HecoDSMDataGenerator: public wfe::AbstractActor
{
public:
	HecoDSMDataGenerator(): _state(READY) { addPort(wfe::IPort::SOURCE); }
	~HecoDSMDataGenerator() { delete sourcePorts()[0]; }
	State state() { return _state; }
	void prefire();
	void fire();
	void postfire();

private:
	wfe::SharedMemory *_item;
	State _state;
};

#endif /* HECODSMDATAGENERATOR_H_ */
