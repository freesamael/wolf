/**
 * \file ACommandListener.cpp
 * \date Jun 14, 2010
 * \author samael
 */

#include <string>
#include <typeinfo>
#include "CTcpTlvReader.h"
#include "ITlvObject.h"
#include "ACommandListener.h"
#include "XTlvCommand.h"

using namespace std;
using namespace cml;

namespace wfe
{

void wfe::ACommandListener::run()
{
	CTcpTlvReader reader(_sock);
	ITlvObject *inobj;
	CTlvCommand *incmd = NULL;

	while (!isDone()) {
		if (!(inobj = reader.readObject()))
			break; // End of file.
		if (!(incmd = dynamic_cast<CTlvCommand *>(inobj))) {
			string type = typeid(inojb).name();
			delete inobj;
			throw XTlvCommand(XTlvCommand::NOT_TLV_COMMAND);
		} else {
			process(incmd);
			delete incmd;
		}
	}
}

}
