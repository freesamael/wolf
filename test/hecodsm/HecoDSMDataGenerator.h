/**
 * \file HecoDSMDataGenerator.h
 * \date Apr 15, 2010
 * \author samael
 */

#ifndef HECODSMDATAGENERATOR_H_
#define HECODSMDATAGENERATOR_H_

#include <AActor.h>
#include <CSharedMemory.h>
#include <IDrop.h>

class HecoDSMDataGenerator: public wolf::AActor
{
public:
	HecoDSMDataGenerator(): _state(READY) { addPort(wolf::IPort::SOURCE); }
	~HecoDSMDataGenerator() { delete sourcePorts()[0]; }
	State state() { return _state; }
	void prefire();
	void fire();
	void postfire();

private:
	wolf::SharedMemory *_item;
	State _state;
};

#endif /* HECODSMDATAGENERATOR_H_ */
