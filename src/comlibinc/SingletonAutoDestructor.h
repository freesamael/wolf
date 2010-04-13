/**
 * \file SingletonAutoDestructor.h
 * \date Apr 7, 2010
 * \author samael
 */

#ifndef SINGLETONAUTODESTRUCTOR_H_
#define SINGLETONAUTODESTRUCTOR_H_

namespace cml
{

/**
 * Auto destructor used to destroy single objects when the program exits.
 */
template <class T>
class SingletonAutoDestructor
{
public:
	~SingletonAutoDestructor() { T::release(); }
};

}

#endif /* SINGLETONAUTODESTRUCTOR_H_ */
