/**
 * \file CMasterSideFinishedWorkerProcessor.cpp
 * \date Jun 29, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "CMasterSideFinishedWorkerProcessor.h"
#include "CMaster.h"

namespace wfe
{

void CMasterSideFinishedWorkerProcessor::run()
{
	PINF_2("Start finish worker processing loop.");
	while (!isDone()) {
		_master->processFinishedWorker();
	}
	PINF_2("Execution loop ends.");
}

}
