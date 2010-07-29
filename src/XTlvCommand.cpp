/**
 * \file XTlvCommand.cpp
 * \date Jul 15, 2010
 * \author samael
 */

#include <cstdio>
#include "XTlvCommand.h"

using namespace std;

namespace wolf
{

const char *XTlvCommand::XTypeString[] = {
		"the incoming message is not a CTlvCommand",
		"received unexpected command",
		"invalid number of parameters for this command"
		"invalid parameter"
};

XTlvCommand::XTlvCommand(XType e, const string &type) throw():
		XWolf((string)XTypeString[e] + " (type = " + type + ")"), _e(e)
{
}

XTlvCommand::XTlvCommand(XType e, const CTlvCommand &cmd) throw():
			XWolf((string)XTypeString[e] + " (cmd = " +
					CTlvCommand::CommandString[cmd.command()] + ")"), _e(e)
{
}

}
