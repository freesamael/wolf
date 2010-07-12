/**
 * \file XSocket.cpp
 * \date Jul 10, 2010
 * \author samael
 */

#include <cstring>
#include "XSocket.h"

using namespace std;

namespace cml
{

XSocket::XSocket(int e) throw():
		_e(ERRNO), _eno(e), _estr(strerror(e))
{

}

XSocket::XSocket(XType e) throw():
		_e(e), _eno(0), _estr()
{
	if (e == INVALID_SOCKET_TYPE)
		_estr = "invalid socket type";
	else if (e == INVALID_SOCKET_STATE)
		_estr = "invalid socket state";
	else
		_estr = "unknown error";
}

}
