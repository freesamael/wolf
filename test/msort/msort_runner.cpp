/**
 * \file msort_runner.cpp
 * \date Jun 28, 2010
 * \author samael
 */

#include <CRunner.h>
#include <CAlwaysFirstWorkerStealer.h>

using namespace wolf;

int main()
{
	CAlwaysFirstWorkerStealer stealer;
	CRunner runner(9527, 7259, &stealer);
	runner.run();
	return 0;
}
