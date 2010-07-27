/**
 * \file AObservable.h
 * \date Apr 11, 2010
 * \author samael
 */

#ifndef AOBSERVABLE_H_
#define AOBSERVABLE_H_

#include <vector>
#include "IObserver.h"

namespace wolf
{

/**
 * An observable object that can notify observers.
 *
 * \see IObserver
 */
class AObservable
{
public:
	AObservable(): _obsrvs() {}
	AObservable(const AObservable &o): _obsrvs(o._obsrvs) {}
	AObservable& operator=(const AObservable &o)
		{ _obsrvs = o._obsrvs; return *this; }
	virtual ~AObservable() {}
	void attach(IObserver *o);
	void detach(IObserver *o);
	void notify();

private:
	std::vector<IObserver *> _obsrvs;
};

}

#endif /* AOBSERVABLE_H_ */
