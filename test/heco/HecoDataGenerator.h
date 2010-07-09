/**
 * \file HecoDataGenerator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef HECODATAGENERATOR_H_
#define HECODATAGENERATOR_H_

#include <AActor.h>

class HecoDataGenerator: public wfe::AActor
{
public:
	HecoDataGenerator(unsigned np);
	~HecoDataGenerator();
	State state() { return _state; }
	void fire();

private:
	State _state;
};

#endif /* HECODATAGENERATOR_H_ */
