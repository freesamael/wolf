/**
 * \file XThread.cpp
 * \date Jul 11, 2010
 * \author samael
 */

#include <cstring>
#include "XThread.h"

using namespace std;

namespace cml
{

XThread::XThread(int e) throw():
		_e(ERRNO), _eno(e), _estr(strerror(e))
{

}

XThread::XThread(XType e) throw():
		_e(e), _eno(0), _estr()
{
	if (e == THREAD_ALREADY_STARTED)
		_estr = "thread already started";
	else
		_estr = "unknown error";
}

}
