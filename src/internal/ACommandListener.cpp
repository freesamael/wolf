/**
 * \file ACommandListener.cpp
 * \date Jun 14, 2010
 * \author samael
 */

#include "ACommandListener.h"

#include <string>
#include <typeinfo>
#include "CTcpTlvReader.h"
#include "ITlvObject.h"
#include "XTlvCommand.h"
#include "HelperMacros.h"

using namespace std;

namespace wolf
{

void wolf::ACommandListener::run()
{
	CTcpTlvReader reader(_sock);

	while (!isDone()) {
		ITlvObject *inobj;
		if (!(inobj = reader.readObject()))
			break; // End of file.
		CTlvCommand *incmd;
		if (!(incmd = dynamic_cast<CTlvCommand *>(inobj))) {
			string type = TYPENAME(inobj);
			delete inobj;
			throw XTlvCommand(XTlvCommand::INVALID_OBJECT, type);
		} else {
			try {
				process(incmd);
			} catch (XTlvCommand &x) {
				delete incmd;
				throw;
			}
			delete incmd;
		}
	}
}

}
