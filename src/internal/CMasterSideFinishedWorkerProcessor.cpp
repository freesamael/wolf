/**
 * \file CMasterSideFinishedWorkerProcessor.cpp
 * \date Jun 29, 2010
 * \author samael
 */

#include "CMasterSideFinishedWorkerProcessor.h"
#include "CMaster.h"

namespace wolf
{

void CMasterSideFinishedWorkerProcessor::run()
{
	while (!isDone()) {
		_master->processFinishedWorker();
	}
}

}
