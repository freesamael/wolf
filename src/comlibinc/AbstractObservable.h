/**
 * \file AbstractObservable.h
 * \date Apr 11, 2010
 * \author samael
 */

#ifndef ABSTRACTOBSERVABLE_H_
#define ABSTRACTOBSERVABLE_H_

#include <vector>
#include "IObserver.h"

namespace cml
{

/**
 * An observable object that can notify observers.
 *
 * \see IObserver
 */
class AbstractObservable
{
public:
	void attach(IObserver *o);
	void detach(IObserver *o);
	inline void notify();

private:
	std::vector<IObserver *> _obsrvs;
};

}

#endif /* ABSTRACTOBSERVABLE_H_ */
