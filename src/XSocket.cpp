/**
 * \file XSocket.cpp
 * \date Jul 10, 2010
 * \author samael
 */

#include <cstring>
#include <cstdio>
#include "XSocket.h"

using namespace std;

namespace wolf
{

const char *XSocket::XTypeString[] = {
		"see errno",
		"invalid socket type",
		"invalid socket state",
		"unknown error"
};

XSocket::XSocket(const string &func, int line, int e) throw():
		XWolf(strerror(e)), _e(ERRNO), _eno(e)
{
}

XSocket::XSocket(const string &func, int line, XType e) throw():
		XWolf(XTypeString[e]), _e(e), _eno(0)
{
}

}
