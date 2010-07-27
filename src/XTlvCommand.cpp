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

XTlvCommand::XTlvCommand(const string &func, int line, XType e,
		const string &type) throw():
		XWolf(XTypeString[e]), _e(e)
{
}

XTlvCommand::XTlvCommand(const std::string &func, int line, XType e,
			const CTlvCommand &cmd) throw():
			XWolf(XTypeString[e]), _e(e)
{
}

}
