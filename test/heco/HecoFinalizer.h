/**
 * \file HecoFinalizer.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef HECOFINALIZER_H_
#define HECOFINALIZER_H_

#include <AActor.h>

class HecoFinalizer: public wfe::AActor
{
public:
	HecoFinalizer(unsigned np);
	~HecoFinalizer();
	State state();
	void fire();

private:
	State _state;
};

#endif /* HECOFINALIZER_H_ */
