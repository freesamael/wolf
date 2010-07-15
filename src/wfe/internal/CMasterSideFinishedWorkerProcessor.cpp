/**
 * \file CMasterSideFinishedWorkerProcessor.cpp
 * \date Jun 29, 2010
 * \author samael
 */

#include "CMasterSideFinishedWorkerProcessor.h"
#include "CMaster.h"

namespace wfe
{

void CMasterSideFinishedWorkerProcessor::run()
{
	while (!isDone()) {
		_master->processFinishedWorker();
	}
}

}
