/**
 * \file ACommandListener.cpp
 * \date Jun 14, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "CTlvReaderWriter.h"
#include "ITlvObject.h"
#include "HelperMacros.h"
#include "ACommandListener.h"

using namespace cml;

namespace wfe
{

void wfe::ACommandListener::run()
{
	CTlvReaderWriter tcprw(_sock);
	ITlvObject *inobj;
	CTlvCommand *incmd = NULL;

	PINF_2("Start listening for commands.");
	while (!isDone()) {
		if (!(inobj = tcprw.read()))
			break; // End of file.
		if (!(incmd = dynamic_cast<CTlvCommand *>(inobj))) {
			PERR("Invalid incoming message.");
			delete inobj;
		} else {
			process(incmd);
			delete incmd;
		}
	}
	PINF_2("Running loop ends.");
}

}
