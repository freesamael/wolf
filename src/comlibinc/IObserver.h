#ifndef IOBSERVER_H_
#define IOBSERVER_H_

namespace cml
{

class AbstractObservable;

/**
 * \interface IObserver
 *
 * Defines the interface for all observer objects.
 */
class IObserver
{
public:
	void update(AbstractObservable *o);
};

}

#endif /* IOBSERVER_H_ */
