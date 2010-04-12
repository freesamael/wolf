/*
 * AbstractObservable.cpp
 *
 *  Created on: Apr 11, 2010
 *      Author: samael
 */

#include "AbstractObservable.h"

using namespace std;

namespace cml
{

/**
 * Attach an observer. If it's already attached, this function takes no effect.
 */
void AbstractObservable::attach(IObserver *o)
{
	for (int i = 0; i < (int)_obsrvs.size(); i++)
		if (_obsrvs[i] == o)
			return;
	_obsrvs.push_back(o);
}

/**
 * Detach an observer. If no proper observer found, this function takes no
 * effect.
 */
void AbstractObservable::detach(IObserver *o)
{
	vector<IObserver *>::iterator iter;
	for (iter = _obsrvs.begin(); iter != _obsrvs.end(); iter++) {
		if (*iter == o) {
			_obsrvs.erase(iter);
			return;
		}
	}
}

/**
 * Notify all observers.
 */
void AbstractObservable::notify()
{
	for (int i = 0; i < (int)_obsrvs.size(); i++)
		_obsrvs[i]->update(this);
}

}
