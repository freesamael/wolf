/**
 * \file Generator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <AbstractActor.h>

class Generator: public wfe::AbstractActor
{
public:
	Generator(unsigned np);
	~Generator();
	State state() { return _state; }
	void fire();

private:
	State _state;
};

#endif /* GENERATOR_H_ */
