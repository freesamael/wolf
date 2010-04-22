/**
 * \file HostAddress.cpp
 * \date Mar 8, 2010
 * \author samael
 */

#include "HostAddress.h"

using namespace std;

namespace cml
{

HostAddress const HostAddress::LocalhostAddress("127.0.0.1");
HostAddress const HostAddress::BroadcastAddress("255.255.255.255");

string HostAddress::toString() const
{
	struct in_addr addr;
	addr.s_addr = _addr;
	return inet_ntoa(addr);
}

}
