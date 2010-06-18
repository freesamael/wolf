/**
 * \file AbstractCommandListener.cpp
 * \date Jun 14, 2010
 * \author samael
 */

#include <iostream>
#include "TLVReaderWriter.h"
#include "ITLVObject.h"
#include "HelperMacros.h"
#include "AbstractCommandListener.h"

using namespace cml;

namespace wfe
{

void wfe::AbstractCommandListener::run()
{
	TLVReaderWriter tcprw(_sock);
	ITLVObject *inobj;
	TLVCommand *incmd = NULL;

	PINF_2("Start listening for commands.");
	while (!isDone()) {
		if (!(inobj = tcprw.read()))
			break; // End of file.
		if (!(incmd = dynamic_cast<TLVCommand *>(inobj))) {
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
