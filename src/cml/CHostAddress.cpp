/**
 * \file CHostAddress.cpp
 * \date Mar 8, 2010
 * \author samael
 */

#include "CHostAddress.h"

using namespace std;

namespace wolf
{

CHostAddress const CHostAddress::LocalhostAddress("127.0.0.1");
CHostAddress const CHostAddress::BroadcastAddress("255.255.255.255");

string CHostAddress::toString() const
{
	struct in_addr addr;
	addr.s_addr = _addr;
	return inet_ntoa(addr);
}

}
