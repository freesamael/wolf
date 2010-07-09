/**
 * \file CWaitCondition.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef CWAITCONDITION_H_
#define CWAITCONDITION_H_

#include <pthread.h>
#include "CMutex.h"

namespace cml
{

/**
 * CWaitCondition implements the conditional variable.
 */
class CWaitCondition
{
public:
	CWaitCondition();
	~CWaitCondition();
	bool wait(CMutex *mutex);
	bool wait(CMutex *mutex, unsigned timeout);
	void wakeOne();
	void wakeAll();

private:
	CWaitCondition(const CWaitCondition &UNUSED(o)): _cond() {}
	CWaitCondition& operator=(const CWaitCondition &UNUSED(o)) { return *this; }
	pthread_cond_t _cond;
};

}

#endif /* CWAITCONDITION_H_ */
