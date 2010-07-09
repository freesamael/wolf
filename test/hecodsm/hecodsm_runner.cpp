/**
 * \file hecodsm_runner.cpp
 * \date Apr 7, 2010
 * \author samael
 */
#include <CRunner.h>

using namespace wfe;

int main()
{
	CRunner runner(6655, 8877, NULL, "hecodsm");
	runner.run();
	return 0;
}
