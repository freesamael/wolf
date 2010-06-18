/**
 * \file testdummyrunner.cpp
 * \date Jun 17, 2010
 * \author samael
 */

#include <Runner.h>

using namespace wfe;

int main()
{
	Runner runner(1234, 5678);
	runner.run();
	return 0;
}
