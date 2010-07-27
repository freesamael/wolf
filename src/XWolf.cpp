/**
 * \file XWolf.cpp
 * \date Jul 27, 2010
 * \author samael
 */

#include "XWolf.h"

#if defined(__GLIBC__) && defined(__GLIBCPP__)
#include <execinfo.h>
#include <cxxabi.h>
#endif

using namespace std;

namespace wolf
{

XWolf::XWolf(const string &remark) throw():
		_estr(remark)
{
#if defined(__GLIBC__) && defined(__GLIBCPP__)
	int nptrs;
	void *buf[128];
	char **cstrs;

	nptrs = backtrace(buf, 128);
	cstrs = backtrace_symbols(buf, nptrs);

	_estr += "\n\tat ";
	for (int i = 0; i < nptrs; i++) {
		_estr += cstrs[i];
		if (i != nptrs - 1)
			_estr += "\n\tby ";
	}
#endif
}

}
