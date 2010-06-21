/**
 * \file SingletonAutoDestructor.h
 * \date Apr 7, 2010
 * \author samael
 */

#ifndef SINGLETONAUTODESTRUCTOR_H_
#define SINGLETONAUTODESTRUCTOR_H_

#include <iostream>
#include <sstream>
#include <typeinfo>
#include "HelperMacros.h"

namespace cml
{

/**
 * Auto destructor used to destroy single objects when the program exits.
 */
template <class T>
class SingletonAutoDestructor
{
public:
	~SingletonAutoDestructor()
		{ PINF_3("Releasing " << TYPENAME(T)); T::release(); }
};

}

#endif /* SINGLETONAUTODESTRUCTOR_H_ */
