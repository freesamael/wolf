/**
 * \file SimpleWorkerStealer.h
 * \date Jun 23, 2010
 * \author samael
 */

#ifndef SIMPLEWORKERSTEALER_H_
#define SIMPLEWORKERSTEALER_H_

#include "Mutex.h"
#include "IWorkerStealer.h"
#include "Runner.h"
#include "HelperMacros.h"

namespace wfe
{

/**
 * Simple, trivial, greedy worker stealer sample.
 */
class SimpleWorkerStealer: public IWorkerStealer
{
public:
	SimpleWorkerStealer(int n = 1);
	SimpleWorkerStealer(const SimpleWorkerStealer &o): IWorkerStealer(),
			_runner(o._runner), _mx(), _stealing(false), _num(o._num) {}
	SimpleWorkerStealer& operator=(const SimpleWorkerStealer &o)
		{ _runner = o._runner; _num = o._num; return *this; }
	inline void setRunner(Runner *runner) { _runner = runner; }
	void workerMissed();
	void stealFailed(cml::TCPSocket *UNUSED(sender)) {}
	void workerArrived(cml::TCPSocket *UNUSED(sender)) {}
	inline bool isStealing()
		{ _mx.lock(); bool s = _stealing; _mx.unlock(); return s; }
	inline void setStealing(bool s)
		{ _mx.lock(); _stealing = s; _mx.unlock(); }

private:
	Runner *_runner;
	cml::Mutex _mx;
	bool _stealing;
	int _num;
};

}

#endif /* SIMPLEWORKERSTEALER_H_ */
