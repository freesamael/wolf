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
		_runner(NULL), _mx()
{
	srand(time(NULL));
}

void SimpleWorkerStealer::workerMissed()
{
	_mx.lock();
	if (_runner) {
		if (!_runner->runnerSocks().empty()) {
			int index = rand() % _runner->runnerSocks().size();
			_runner->sendWorkerSteal(_runner->runnerSocks()[index], 10);
		}
	}
	_mx.unlock();
}

void SimpleWorkerStealer::stealFailed(TCPSocket *UNUSED(sender))
{

}

void SimpleWorkerStealer::workerArrived(TCPSocket *UNUSED(sender))
{

}

}
