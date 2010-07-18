/**
 * \file manset_runner.cpp
 * \date Jul 16, 2010
 * \author samael
 */

#include <CRunner.h>
#include <CSimpleWorkerStealer.h>

using namespace wfe;

int main()
{
	CSimpleWorkerStealer stealer(10);
	CRunner runner(5566, 7788, &stealer);
	runner.run();
	return 0;
}
