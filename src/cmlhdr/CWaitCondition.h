/**
 * \file CWaitCondition.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef CWAITCONDITION_H_
#define CWAITCONDITION_H_

#include <pthread.h>
#include "CMutex.h"
#include "XThread.h"
#include "HelperMacros.h"

namespace wolf
{

/**
 * CWaitCondition encapsulates the conditional variable.
 */
class CWaitCondition
{
public:
	CWaitCondition() throw(XThread);
	~CWaitCondition() throw();
	bool wait(CMutex *mutex) throw(XThread);
	bool wait(CMutex *mutex, unsigned timeout_us) throw(XThread);
	void wakeOne() throw(XThread);
	void wakeAll() throw(XThread);

private:
	CWaitCondition(const CWaitCondition &UNUSED(o)): _cond() {}
	CWaitCondition& operator=(const CWaitCondition &UNUSED(o)) { return *this; }
	pthread_cond_t _cond;
};

}

#endif /* CWAITCONDITION_H_ */
