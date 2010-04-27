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
	AbstractObservable(): _obsrvs() {}
	AbstractObservable(const AbstractObservable &o): _obsrvs(o._obsrvs) {}
	AbstractObservable& operator=(const AbstractObservable &o)
		{ _obsrvs = o._obsrvs; return *this; }
	virtual ~AbstractObservable() {}
	void attach(IObserver *o);
	void detach(IObserver *o);
	void notify();

private:
	std::vector<IObserver *> _obsrvs;
};

}

#endif /* ABSTRACTOBSERVABLE_H_ */
