/**
 * \file XTlvObject.cpp
 * \date Jul 14, 2010
 * \author samael
 */

#include <cstdio>
#include "XTlvObject.h"

using namespace std;

namespace cml
{

const char *XTlvObject::XTypeString[] = {
		"invalid type id",
		"no suitable creator",
		"null block generated"
};

XTlvObject::XTlvObject(const std::string &func, int line, XType e, uint16_t id,
		const std::string &name) throw():
		_e(e), _estr()
{
	char idstr[10];
	sprintf(idstr, "%d", (int)id);

	char lstr[10];
	sprintf(lstr, "%d", (int)line);

	_estr = (string)XTypeString[e] + " (id: " + idstr + ", name: " + name + ")"
			+ " [" + func + lstr + "]";
}

}
