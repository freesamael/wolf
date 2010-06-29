/**
 * \file MasterSideFinishedWorkerProcessor.h
 * \date Jun 29, 2010
 * \author samael
 */

#ifndef MASTERSIDEFINISHEDWORKERPROCESSOR_H_
#define MASTERSIDEFINISHEDWORKERPROCESSOR_H_

#include "IRunnable.h"
#include "Mutex.h"

namespace wfe
{

class Master;

/**
 * Used to process finished workers.
 */
class MasterSideFinishedWorkerProcessor: public cml::IRunnable
{
public:
	MasterSideFinishedWorkerProcessor(Master *m):
		_master(m), _done(false), _mx() {}
	MasterSideFinishedWorkerProcessor(const MasterSideFinishedWorkerProcessor &o):
		IRunnable(), _master(o._master), _done(o._done), _mx() {}
	MasterSideFinishedWorkerProcessor& operator=(const MasterSideFinishedWorkerProcessor &o)
		{ _master = o._master; _done = o._done; return *this; }
	void run();
	inline bool isDone()
		{ _mx.lock(); bool d = _done; _mx.unlock(); return d; }
	inline void setDone(bool d = true)
		{ _mx.lock(); _done = d; _mx.unlock(); }

private:
	Master *_master;
	bool _done;
	cml::Mutex _mx;
};

}

#endif /* MASTERSIDEFINISHEDWORKERPROCESSOR_H_ */
