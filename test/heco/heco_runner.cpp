/**
 * \file heco_runner.cpp
 * \date Jun 20, 2010
 * \author samael
 */
#include <Runner.h>
#include <SimpleWorkerStealer.h>

using namespace wfe;

int main()
{
	SimpleWorkerStealer stealer(10);
	Runner runner(5566, 7788, &stealer);
	runner.run();
	return 0;
}
