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
	void update(AbstractObservable *o);
};

}

#endif /* IOBSERVER_H_ */
