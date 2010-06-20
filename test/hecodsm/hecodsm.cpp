/*
 * hecodsm.cpp
 *
 *  Created on: Apr 7, 2010
 *      Author: samael
 */

#include <Director.h>
#include <SimpleWorkflowExecutor.h>
#include <ManagerActor.h>
#include "NumberGenerator.h"
#include "NumberLoader.h"
#include "Counter.h"
#include "CounterCreator.h"

using namespace wfe;

int main()
{
	SimpleWorkflowExecutor exec;
	Director d(&exec);

	NumberGenerator a1;
	Counter w1;
	ManagerActor a2(&w1);
	NumberLoader a3;
	Channel *ch1 = d.createChannel("ch1");
	Channel *ch2 = d.createChannel("ch2");

	a1.sourcePorts()[0]->setChannel(ch1);
	a2.sinkPorts()[0]->setChannel(ch1);
	a2.sourcePorts()[0]->setChannel(ch2);
	a3.sinkPorts()[0]->setChannel(ch2);

	d.addActor(&a1);
	d.addActor(&a2);
	d.addActor(&a3);

	d.execute(6655, 8877, "hecodsm");

	return 0;
}
