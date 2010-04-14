/*
 * heco.cpp
 *
 *  Created on: Apr 7, 2010
 *      Author: samael
 */

#include <Director.h>
#include <SimpleWorkflowExecutor.h>

using namespace wfe;

int main()
{
	SimpleWorkflowExecutor exec;
	Director d(&exec);

	d.execute(6655, 8877, "heco");

	return 0;
}
