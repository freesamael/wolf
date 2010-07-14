/**
 * \file XSocket.cpp
 * \date Jul 10, 2010
 * \author samael
 */

#include <cstring>
#include <cstdio>
#include "XSocket.h"

using namespace std;

namespace cml
{

const char *XSocket::XTypeString[] = {
		"see errno",
		"invalid socket type",
		"invalid socket state",
		"unknown error"
};

XSocket::XSocket(const char *func, int line, int e) throw():
		_e(ERRNO), _eno(e), _estr()
{
	char lstr[10];
	sprintf(lstr, "%d", line);

	_estr = (string)strerror(e) + " [" + func + ": " + lstr + "]";
}

XSocket::XSocket(const char *func, int line, XType e) throw():
		_e(e), _eno(0), _estr()
{
	char lstr[10];
	sprintf(lstr, "%d", line);

	_estr = (string)XTypeString[e] + " [" + func + ": " + lstr + "]";
}

}
