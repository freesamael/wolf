/**
 * \file AbstractObservable.cpp
 * \date Apr 11, 2010
 * \author samael
 */

#include "AbstractObservable.h"

using namespace std;

namespace cml
{

/**
 * Attach an observer. It takes no effect if the observer is already attached.
 */
void AbstractObservable::attach(IObserver *o)
{
	for (int i = 0; i < (int)_obsrvs.size(); i++)
		if (_obsrvs[i] == o)
			return;
	_obsrvs.push_back(o);
}

/**
 * Detach an observer. It takes no effect if the observer was not attached
 * before.
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