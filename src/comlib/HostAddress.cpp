/*
 * HostAddress.cpp
 *
 *  Created on: Mar 8, 2010
 *      Author: samael
 */

#include "HostAddress.h"

using namespace std;

namespace cml
{

string HostAddress::toString() const
{
	struct in_addr addr;
	addr.s_addr = _addr;
	return inet_ntoa(addr);
}

}
