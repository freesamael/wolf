/**
 * \file XThread.cpp
 * \date Jul 11, 2010
 * \author samael
 */

#include <cstring>
#include <cstdio>
#include "XThread.h"

using namespace std;

namespace cml
{

const char *XThread::XTypeString[] = {
		"see errno",
		"thread already started",
		"unknown error"
};

XThread::XThread(const char *func, int line, int e) throw():
		_e(ERRNO), _eno(e), _estr()
{
	char lstr[10];
	sprintf(lstr, "%d", line);

	_estr = (string)strerror(e) + " [" + func + ": " + lstr + "]";
}

XThread::XThread(const char *func, int line, XType e) throw():
		_e(e), _eno(0), _estr()
{
	char lstr[10];
	sprintf(lstr, "%d", line);

	_estr = (string)XTypeString[e] + " [" + func + ": " + lstr + "]";
}

XThread::XThread(const XThread &o) throw():
		_e(o._e), _eno(o._eno), _estr(o._estr)
{

}

XThread& XThread::operator=(const XThread &o) throw()
{
	if (&o != this) {
		_e = o._e;
		_eno = o._eno;
		_estr = o._estr;
	}
	return *this;
}

}
