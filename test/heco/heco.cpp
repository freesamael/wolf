/*
 * heco.cpp
 *
 *  Created on: Apr 7, 2010
 *      Author: samael
 */

#include <Director.h>
#include <SimpleWorkflowExecutor.h>
#include <RunnerAgent.h>
#include "RandomNumberGeneratorActor.h"
#include "NumberReaderActor.h"

using namespace wfe;

int main()
{
	SimpleWorkflowExecutor exec;
	Director d(&exec);

	RandomNumberGeneratorActor *a1 = new RandomNumberGeneratorActor();
	NumberReaderActor *a2 = new NumberReaderActor();
	d.addActor(a1);
	d.addActor(a2);

	Channel *c1 = d.createChannel("ch1");
	a1->outports()[0]->setChannel(c1);
	a2->inports()[0]->setChannel(c1);

	RunnerAgent::instance()->setup(5566, 7788, "heco");

	d.execute();

	return 0;
}
