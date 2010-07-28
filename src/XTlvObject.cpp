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

string gennote(uint16_t id, const std::string &name)
{
	char idstr[10];
	if (id == TLV_TYPE_INVALID)
		sprintf(idstr, "?");
	else
		sprintf(idstr, "%d", (int)id);

	return (string)" (id: " + idstr + ", name: " + name + ")";

}

XTlvObject::XTlvObject(XType e, uint16_t id, const std::string &name) throw():
		XWolf((string)XTypeString[e] + gennote(id, name)), _e(e)
{
}

}
