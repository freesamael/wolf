/**
 * \file CSimpleWorkerStealer.h
 * \date Jun 23, 2010
 * \author samael
 */

#ifndef CSIMPLEWORKERSTEALER_H_
#define CSIMPLEWORKERSTEALER_H_

#include "CMutex.h"
#include "IWorkerStealer.h"
#include "CRunner.h"
#include "HelperMacros.h"

namespace wfe
{

/**
 * Simple, trivial, greedy worker stealer sample.
 */
class CSimpleWorkerStealer: public IWorkerStealer
{
public:
	CSimpleWorkerStealer(int n = 1);
	CSimpleWorkerStealer(const CSimpleWorkerStealer &o): IWorkerStealer(),
			_runner(o._runner), _mx(), _stealing(false), _num(o._num) {}
	CSimpleWorkerStealer& operator=(const CSimpleWorkerStealer &o)
		{ _runner = o._runner; _num = o._num; return *this; }
	inline void setRunner(CRunner *runner) { _runner = runner; }
	void workerMissed();
	void stealFailed(cml::CTcpSocket *UNUSED(sender)) {}
	void workerArrived(cml::CTcpSocket *UNUSED(sender)) {}
	inline bool isStealing()
		{ _mx.lock(); bool s = _stealing; _mx.unlock(); return s; }
	inline void setStealing(bool s)
		{ _mx.lock(); _stealing = s; _mx.unlock(); }

private:
	CRunner *_runner;
	cml::CMutex _mx;
	bool _stealing;
	int _num;
};

}

#endif /* CSIMPLEWORKERSTEALER_H_ */
