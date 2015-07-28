/**
 * \file HelperMacros.cpp
 * \date Jun 21, 2010
 * \author samael
 */

#include <pthread.h>
#include <string>
#include <cstdlib>

#ifdef __DEMANGLE__
#include <cxxabi.h>
#endif

using namespace std;

namespace wolf
{

pthread_mutex_t g_mxcout = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mxcerr = PTHREAD_MUTEX_INITIALIZER;

string demangle(const char *manglename)
{
#ifdef __DEMANGLE__
  int status;
  char *cname = abi::__cxa_demangle(manglename, NULL, NULL, &status);
  std::string name(cname);
  free(cname);
  return name;
#endif
  return manglename;
}

}
