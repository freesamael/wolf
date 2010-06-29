/**
 * \file AlwaysFirstWorkerStealer.h
 * \date Jun 26, 2010
 * \author samael
 */

#ifndef ALWAYSFIRSTWORKERSTEALER_H_
#define ALWAYSFIRSTWORKERSTEALER_H_

#include "IWorkerStealer.h"
#include "Runner.h"
#include "HelperMacros.h"
#include "Mutex.h"

namespace wfe
{

class AlwaysFirstWorkerStealer: public IWorkerStealer
{
public:
	AlwaysFirstWorkerStealer(int n = 1):
		_num(n), _runner(NULL), _mx(), _stealing(false) {}
	AlwaysFirstWorkerStealer(const AlwaysFirstWorkerStealer &o):
		IWorkerStealer(), _num(o._num), _runner(o._runner), _mx(),
		_stealing(false) {}
	AlwaysFirstWorkerStealer& operator=(const AlwaysFirstWorkerStealer &o)
		{ _num = o._num; _runner = o._runner; return *this; }
	inline void setRunner(Runner *runner) { _runner = runner; }
	void workerMissed();
	void stealFailed(cml::TCPSocket *UNUSED(sender)) {}
	void workerArrived(cml::TCPSocket *UNUSED(sender)) {}
	inline bool isStealing()
		{ _mx.lock(); bool s = _stealing; _mx.unlock(); return s; }
	inline void setStealing(bool s)
		{ _mx.lock(); _stealing = s; _mx.unlock(); }

private:
	int _num;
	Runner *_runner;
	cml::Mutex _mx;
	bool _stealing;
};

}

#endif /* ALWAYSFIRSTWORKERSTEALER_H_ */
