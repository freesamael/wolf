/**
 * \file XThread.cpp
 * \date Jul 11, 2010
 * \author samael
 */

#include <cstring>
#include <cstdio>
#include "XThread.h"

using namespace std;

namespace wolf
{

const char *XThread::XTypeString[] = {
		"see errno",
		"thread already started",
		"unknown error"
};

XThread::XThread(const string &func, int line, int e) throw():
		XWolf(strerror(e)), _e(ERRNO), _eno(e)
{
}

XThread::XThread(const string &func, int line, XType e) throw():
		XWolf(XTypeString[e]), _e(e), _eno(0)
{
}

}
