/**
 * \file WaitCondition.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef WAITCONDITION_H_
#define WAITCONDITION_H_

#include <pthread.h>
#include "Mutex.h"

namespace cml
{

/**
 * WaitCondition implements the conditional variable.
 */
class WaitCondition
{
public:
	WaitCondition();
	~WaitCondition();
	bool wait(Mutex *mutex);
	bool wait(Mutex *mutex, unsigned timeout);
	void wakeOne();
	void wakeAll();

private:
	WaitCondition(const WaitCondition &UNUSED(o)): _cond() {}
	WaitCondition& operator=(const WaitCondition &UNUSED(o)) { return *this; }
	pthread_cond_t _cond;
};

}

#endif /* WAITCONDITION_H_ */
