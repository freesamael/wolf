/*
 * XTlvCommand.cpp
 *
 *  Created on: Jul 15, 2010
 *      Author: samael
 */

#include <cstring>
#include "XTlvCommand.h"

using namespace std;

namespace wfe
{

const char *XTlvCommand::XTypeString[] = {
		"the incoming message is not a CTlvCommand"
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

}
