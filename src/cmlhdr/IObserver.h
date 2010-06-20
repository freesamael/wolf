/**
 * \file IObserver.h
 * \date Apr 11, 2010
 * \author samael
 */

#ifndef IOBSERVER_H_
#define IOBSERVER_H_

namespace cml
{

class AbstractObservable;

/**
 * \interface IObserver
 *
 * IObserver defines the interface for all observer objects.
 */
class IObserver
{
public:
	virtual ~IObserver() {}
	/// Update the observer.
	virtual void update(AbstractObservable *o) = 0;
};

}

#endif /* IOBSERVER_H_ */
