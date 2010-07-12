/**
 * \file CMasterSideFinishedWorkerProcessor.h
 * \date Jun 29, 2010
 * \author samael
 */

#ifndef CMASTERSIDEFINISHEDWORKERPROCESSOR_H_
#define CMASTERSIDEFINISHEDWORKERPROCESSOR_H_

#include "IRunnable.h"
#include "CMutex.h"

namespace wfe
{

class CMaster;

/**
 * Used to process finished workers.
 */
class CMasterSideFinishedWorkerProcessor: public cml::IRunnable
{
public:
	CMasterSideFinishedWorkerProcessor(CMaster *m):
		_master(m), _done(false), _mx() {}
	CMasterSideFinishedWorkerProcessor(const CMasterSideFinishedWorkerProcessor &o):
		IRunnable(), _master(o._master), _done(o._done), _mx() {}
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
	cml::CMutex _mx;
};

}

#endif /* CMASTERSIDEFINISHEDWORKERPROCESSOR_H_ */