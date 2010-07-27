/*
 * XTlvCommand.cpp
 *
 *  Created on: Jul 15, 2010
 *      Author: samael
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
		_e(e), _estr()
{
	char lstr[10];
	sprintf(lstr, "%d", line);

	_estr = (string)XTypeString[e] + " (type = " + type + ") [" + func + ": " +
			lstr + "]";
}

XTlvCommand::XTlvCommand(const std::string &func, int line, XType e,
			const CTlvCommand &cmd) throw():
			_e(e), _estr()
{
	char lstr[10];
	sprintf(lstr, "%d", line);

	_estr = (string)XTypeString[e] + " (cmd = " +
			CTlvCommand::CommandString[cmd.command()] + ") [" + func + ": " +
			lstr + "]";
}

}
