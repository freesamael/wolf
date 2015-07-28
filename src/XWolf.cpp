/**
 * \file XWolf.cpp
 * \date Jul 27, 2010
 * \author samael
 */

#include "XWolf.h"

#include <cstdlib>
#include <ctype.h>
#include "HelperMacros.h"

#ifdef __DEMANGLE__
#include <cxxabi.h>
#endif

#if defined(__DEBUG__) && (defined(__GLIBC__) || defined(__USE_LIBEXECINFO) \
			|| (defined(__APPLE__) && defined(__MACH__)))
#define __BACKTRACE__	1
#include <execinfo.h>
#endif

using namespace std;

namespace wolf
{

/**
 * The symbol string might be like: <br>
 *     bin/manset_runner(_ZN4wolf5XWolfC2ERKSs+0x4b) [0x8085489] on Linux or<br>
 *     0   testexception  0x000029a4 _ZN4wolf5XWolfC1ERKSs + 88  on Mac. <br>
 * Hence, characters start from '_' and before non-digit/alpha is the mangle string.
 */
string demangle(char *symbol)
{
#ifdef __DEMANGLE__
  int begin = 0, end = 0;

  // Find end (the character next to the last character in mangle string).
  int candidate = 0;
  for (int i = 0; symbol[i] != '\0'; i++) {
    if (isdigit(symbol[i]) || isalpha(symbol[i])) {
      candidate = i;
    } else if (symbol[i] == '+') {
      end = candidate + 1;
      break;
    }
  }

  // Find begin (first character in mangle string).
  for (int i = candidate; i >= 0 ; i--) {
    if (!isdigit(symbol[i]) && !isalpha(symbol[i]) && symbol[i] != '_') {
      begin = i + 1;
      break;
    }
  }

  // Demangle.
  if (begin && end && begin != end) {
    string str;
    char *cstr;
    char originalend = symbol[end];

    symbol[end] = '\0';
    int status;
    if ((cstr = abi::__cxa_demangle(symbol + begin, NULL, NULL, &status))) {
      str = cstr;
      free(cstr);
    } else {
      str = (string)(symbol + begin) + "()";
    }

    symbol[end] = originalend;
    return str;
  }
#endif
  return symbol;
}

XWolf::XWolf(const string &remark) throw():
		_estr(remark)
{
#ifdef __BACKTRACE__
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
