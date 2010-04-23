/**
 * \file IRunnable.h
 * \date Apr 21, 2010
 * \author samael
 */

#ifndef IRUNNABLE_H_
#define IRUNNABLE_H_

namespace cml
{

/**
 * \interface IRunnable
 * IRunnable defines an interface of objects that can be executed by Thread.
 */
class IRunnable
{
public:
	virtual void run() = 0;
};

}

#endif /* IRUNNABLE_H_ */
