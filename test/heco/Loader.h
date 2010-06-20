/**
 * \file Loader.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef LOADER_H_
#define LOADER_H_

#include <AbstractActor.h>

class Loader: public wfe::AbstractActor
{
public:
	Loader(unsigned np);
	~Loader();
	State state();
	void fire();

private:
	State _state;
};

#endif /* LOADER_H_ */
