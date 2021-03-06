/**
 * \file CAlwaysFirstWorkerStealer.h
 * \date Jun 26, 2010
 * \author samael
 */

#ifndef CALWAYSFIRSTWORKERSTEALER_H_
#define CALWAYSFIRSTWORKERSTEALER_H_

#include "IWorkerStealer.h"
#include "CRunner.h"
#include "HelperMacros.h"
#include "CMutex.h"

namespace wolf
{

/**
 * A stealing policy that always steals from first runner.
 *
 * \see IWorkerStealer
 */
class CAlwaysFirstWorkerStealer: public IWorkerStealer
{
public:
	CAlwaysFirstWorkerStealer(int n = 1):
		_num(n), _runner(NULL), _mx(), _stealing(false) {}
	CAlwaysFirstWorkerStealer(const CAlwaysFirstWorkerStealer &o):
		IWorkerStealer(), _num(o._num), _runner(o._runner), _mx(),
		_stealing(false) {}
	CAlwaysFirstWorkerStealer& operator=(const CAlwaysFirstWorkerStealer &o)
		{ _num = o._num; _runner = o._runner; return *this; }
	inline void setRunner(CRunner *runner) { _runner = runner; }
	void workerMissed();
	void stealFailed(CTcpSocket *UNUSED(sender)) {}
	void workerArrived(CTcpSocket *UNUSED(sender)) {}
	inline bool isStealing()
		{ _mx.lock(); bool s = _stealing; _mx.unlock(); return s; }
	inline void setStealing(bool s)
		{ _mx.lock(); _stealing = s; _mx.unlock(); }

private:
	int _num;
	CRunner *_runner;
	CMutex _mx;
	bool _stealing;
};

}

#endif /* CALWAYSFIRSTWORKERSTEALER_H_ */
