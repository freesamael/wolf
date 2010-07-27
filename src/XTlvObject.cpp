/**
 * \file XTlvObject.cpp
 * \date Jul 14, 2010
 * \author samael
 */

#include <cstdio>
#include "XTlvObject.h"
#include "CmlTLVTypes.h"

using namespace std;

namespace wolf
{

const char *XTlvObject::XTypeString[] = {
		"invalid type id",
		"no suitable creator found",
		"a null block generated",
		"the block is too short to be a TLV object"
};

XTlvObject::XTlvObject(const std::string &func, int line, XType e, uint16_t id,
		const std::string &name) throw():
		_e(e), _estr()
{
	char idstr[10];
	if (id == TLV_TYPE_INVALID)
		sprintf(idstr, "?");
	else
		sprintf(idstr, "%d", (int)id);

	char lstr[10];
	sprintf(lstr, "%d", (int)line);

	_estr = (string)XTypeString[e] + " (id: " + idstr + ", name: " + name +
			") [" + func + ": " + lstr + "]";
}

}
