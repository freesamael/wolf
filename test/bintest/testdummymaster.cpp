/**
 * \file testdummymaster.cpp
 * \date Jun 17, 2010
 * \author samael
 */

#include <CDirector.h>
#include <CSimpleWorkflowExecutor.h>

using namespace wolf;

int main()
{
	CSimpleWorkflowExecutor exec;
	CDirector d(&exec);

	d.execute(1234, 5678);

	return 0;
}
