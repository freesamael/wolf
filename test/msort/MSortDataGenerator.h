/**
 * \file MSortDataGenerator.h
 * \date Jun 28, 2010
 * \author samael
 */

#ifndef MSORTDATAGENERATOR_H_
#define MSORTDATAGENERATOR_H_

#include <stdint.h>
#include <AbstractActor.h>

class MSortDataGenerator: public wfe::AbstractActor
{
public:
	MSortDataGenerator(int nports, int psize);
	~MSortDataGenerator();
	void prefire() { _state = RUNNING; }
	void fire();
	void postfire() { _state = FINISHED; }
	State state() { return _state; }

private:
	int _np, _psize;
	State _state;
};

#endif /* MSORTDATAGENERATOR_H_ */
