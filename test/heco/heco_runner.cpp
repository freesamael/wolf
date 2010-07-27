/**
 * \file heco_runner.cpp
 * \date Jun 20, 2010
 * \author samael
 */
#include <CRunner.h>
#include <CSimpleWorkerStealer.h>

using namespace wolf;

int main()
{
	CSimpleWorkerStealer stealer(10);
	CRunner runner(5566, 7788, &stealer);
	runner.run();
	return 0;
}
