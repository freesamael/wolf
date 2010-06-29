/**
 * \file msort_runner.cpp
 * \date Jun 28, 2010
 * \author samael
 */

#include <Runner.h>
#include <AlwaysFirstWorkerStealer.h>

using namespace wfe;

int main()
{
	AlwaysFirstWorkerStealer stealer;
	Runner runner(9527, 7259, &stealer);
	runner.run();
	return 0;
}
