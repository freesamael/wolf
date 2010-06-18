/**
 * \file testdummymaster.cpp
 * \date Jun 17, 2010
 * \author samael
 */

#include <Director.h>
#include <SimpleWorkflowExecutor.h>

using namespace wfe;

int main()
{
	SimpleWorkflowExecutor exec;
	Director d(&exec);

	d.execute(1234, 5678);

	return 0;
}
