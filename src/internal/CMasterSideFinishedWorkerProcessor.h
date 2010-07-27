/**
 * \file CMasterSideFinishedWorkerProcessor.h
 * \date Jun 29, 2010
 * \author samael
 */

#ifndef CMASTERSIDEFINISHEDWORKERPROCESSOR_H_
#define CMASTERSIDEFINISHEDWORKERPROCESSOR_H_

#include "CThread.h"
#include "CMutex.h"

namespace wolf
{

class CMaster;

/**
 * Used to process finished workers.
 */
class CMasterSideFinishedWorkerProcessor: public CThread
{
public:
	CMasterSideFinishedWorkerProcessor(CMaster *m):
		_master(m), _done(false), _mx() {}
	CMasterSideFinishedWorkerProcessor(const CMasterSideFinishedWorkerProcessor &o):
		CThread(), _master(o._master), _done(o._done), _mx() {}
	CMasterSideFinishedWorkerProcessor& operator=(const CMasterSideFinishedWorkerProcessor &o)
		{ _master = o._master; _done = o._done; return *this; }
	void run();
	inline bool isDone()
		{ _mx.lock(); bool d = _done; _mx.unlock(); return d; }
	inline void setDone(bool d = true)
		{ _mx.lock(); _done = d; _mx.unlock(); }

private:
	CMaster *_master;
	bool _done;
	CMutex _mx;
};

}

#endif /* CMASTERSIDEFINISHEDWORKERPROCESSOR_H_ */
