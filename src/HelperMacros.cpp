/**
 * \file HelperMacros.cpp
 * \date Jun 21, 2010
 * \author samael
 */

#include <pthread.h>
#include <string>
#include <cstdlib>
#if defined(__GLIBCXX__) || defined(__clang__)
#include <cxxabi.h>
#endif

pthread_mutex_t g_mxcout = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mxcerr = PTHREAD_MUTEX_INITIALIZER;

std::string demangle(const char *manglename)
{
#if defined(__GLIBCXX__) || defined(__clang__)
	int status;
	char *cname = abi::__cxa_demangle(manglename, NULL, NULL, &status);
	std::string name(cname);
	free(cname);
	return name;
#else  // ! (defined(__GLIBCXX__) || defined(__clang__))
  return manglename;
#endif // defined(__GLIBCXX__) || defined(__clang__)
}
