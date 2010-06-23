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

namespace wfe
{

/**
 * Simple, trivial, greedy worker stealer sample.
 */
class SimpleWorkerStealer: public IWorkerStealer
{
public:
	SimpleWorkerStealer();
	SimpleWorkerStealer(const SimpleWorkerStealer &o): IWorkerStealer(),
			_runner(o._runner), _mx() {}
	SimpleWorkerStealer& operator=(const SimpleWorkerStealer &o)
		{ _runner = o._runner; return *this; }
	void setRunner(Runner *runner)
		{ _mx.lock(); _runner = runner; _mx.unlock(); }
	void workerMissed();
	void stealFailed(cml::TCPSocket *sender);
	void workerArrived(cml::TCPSocket *sender);

private:
	Runner *_runner;
	cml::Mutex _mx;
};

}

#endif /* SIMPLEWORKERSTEALER_H_ */
