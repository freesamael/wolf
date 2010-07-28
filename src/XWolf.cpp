/**
 * \file XWolf.cpp
 * \date Jul 27, 2010
 * \author samael
 */

#include <cstdlib>
#include "XWolf.h"

#if defined(__GLIBC__)
#include <execinfo.h>
#endif

#if defined(__GLIBCXX__)
#include <cxxabi.h>
#endif

using namespace std;

namespace wolf
{

/**
 * The symbol string is like:
 *     bin/manset_runner(_ZN4wolf5XWolfC2ERKSs+0x4b) [0x8085489]
 *
 * Hence, characters between '(' and '+' is the mangle string.
 */
string demangle(char *symbol)
{
#if defined(__GLIBCXX__)
	int begin = 0, end = 0;

	// Find begin.
	for (int i = 0; symbol[i] != '\0'; i++)
		if (symbol[i] == '(')
			begin = i + 1;

	// Find end.
	for (int i = begin; symbol[i] != '\0'; i++)
		if (symbol[i] == '+')
			end = i;

	// Demangle.
	if (begin && end) {
		string str;
		symbol[end] = '\0';
		int status;
		char *cstr = abi::__cxa_demangle(symbol + begin, NULL, NULL, &status);
		str = cstr;
		free(cstr);
		symbol[end] = '+';
		return str;
	}
#endif

	return symbol;
}

XWolf::XWolf(const string &remark) throw():
		_estr(remark)
{
#if defined(__GLIBC__)
	int nptrs;
	void *buf[128];
	char **cstrs;

	nptrs = backtrace(buf, 128);
	cstrs = backtrace_symbols(buf, nptrs);

	_estr += "\n\tat ";
	for (int i = 0; i < nptrs; i++) {
		_estr += demangle(cstrs[i]);
		if (i != nptrs - 1)
			_estr += "\n\tby ";
	}

	free(cstrs);
#endif
}

}
