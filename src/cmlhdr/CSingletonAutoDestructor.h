/**
 * \file CSingletonAutoDestructor.h
 * \date Apr 7, 2010
 * \author samael
 */

#ifndef CSINGLETONAUTODESTRUCTOR_H_
#define CSINGLETONAUTODESTRUCTOR_H_

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
class CSingletonAutoDestructor
{
public:
	~CSingletonAutoDestructor() { T::release(); }
};

}

#endif /* CSINGLETONAUTODESTRUCTOR_H_ */
