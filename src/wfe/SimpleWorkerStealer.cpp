/**
 * \file SimpleWorkerStealer.cpp
 * \date Jun 23, 2010
 * \author samael
 */

#include <ctime>
#include <cstdlib>
#include "HelperMacros.h"
#include "WaitCondition.h"
#include "SimpleWorkerStealer.h"

using namespace std;
using namespace cml;

namespace wfe
{

SimpleWorkerStealer::SimpleWorkerStealer():
		_runner(NULL), _mx(), _stealing(false)
{
	srand(time(NULL));
}

void SimpleWorkerStealer::workerMissed()
{
	if (!_stealing) {
		_mx.lock();
		bool s = _stealing;
		_stealing = true;
		_mx.unlock();

		if (s)
			steal();

		_mx.lock();
		_stealing = false;
		_mx.unlock();
	}
}

void SimpleWorkerStealer::steal()
{
	if (_runner) {
		if (!_runner->runnerSocks().empty()) {
			int index = rand() % _runner->runnerSocks().size();
			_runner->sendWorkerSteal(_runner->runnerSocks()[index], 1);
		}
	}
}

void SimpleWorkerStealer::stealFailed(TCPSocket *UNUSED(sender))
{

}

void SimpleWorkerStealer::workerArrived(TCPSocket *UNUSED(sender))
{

}

}
