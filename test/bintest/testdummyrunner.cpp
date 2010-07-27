/**
 * \file testdummyrunner.cpp
 * \date Jun 17, 2010
 * \author samael
 */

#include <CRunner.h>
#include <CSimpleWorkerStealer.h>

using namespace wolf;

int main()
{
	CSimpleWorkerStealer stealer;
	CRunner runner(1234, 5678, &stealer);
	runner.run();
	return 0;
}
