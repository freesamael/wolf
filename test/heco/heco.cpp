/*
 * heco.cpp
 *
 *  Created on: Apr 7, 2010
 *      Author: samael
 */

#include <Director.h>
#include <SimpleWorkflowExecutor.h>
#include <ManagerActor.h>
#include "HelloWorker.h"
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
	NumberLoader a3;
	Channel *ch1 = d.createChannel("ch1");

	a1.sinkPorts()[0]->setChannel(ch1);
	a3.sourcePorts()[0]->setChannel(ch1);

	d.addActor(&a1);
	d.addActor(&a3);

	d.execute(6655, 8877, "heco");

	return 0;
}
