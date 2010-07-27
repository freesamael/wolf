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
		XWolf(XTypeString[e]), _e(e)
{
}

}
