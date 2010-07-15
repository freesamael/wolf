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

XThread::XThread(const string &func, int line, int e) throw():
		_e(ERRNO), _eno(e), _estr()
{
	char lstr[10];
	sprintf(lstr, "%d", line);

	_estr = (string)strerror(e) + " [" + func + ": " + lstr + "]";
}

XThread::XThread(const string &func, int line, XType e) throw():
		_e(e), _eno(0), _estr()
{
	char lstr[10];
	sprintf(lstr, "%d", line);

	_estr = (string)XTypeString[e] + " [" + func + ": " + lstr + "]";
}

}
