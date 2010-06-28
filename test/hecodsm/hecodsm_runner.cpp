/**
 * \file hecodsm_runner.cpp
 * \date Apr 7, 2010
 * \author samael
 */
#include <Runner.h>

using namespace wfe;

int main()
{
	Runner runner(6655, 8877, NULL, "hecodsm");
	runner.run();
	return 0;
}
