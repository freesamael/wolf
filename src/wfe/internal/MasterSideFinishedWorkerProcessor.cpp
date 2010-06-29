/**
 * \file MasterSideFinishedWorkerProcessor.cpp
 * \date Jun 29, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "MasterSideFinishedWorkerProcessor.h"
#include "Master.h"

namespace wfe
{

void MasterSideFinishedWorkerProcessor::run()
{
	PINF_2("Start finish worker processing loop.");
	while (!isDone()) {
		_master->processFinishedWorker();
	}
	PINF_2("Execution loop ends.");
}

}
