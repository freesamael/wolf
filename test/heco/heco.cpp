/**
 * \file heco.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <ConcurrentWorkflowExecutor.h>
#include <Director.h>
#include <ManagerActor.h>
#include <Master.h>
#include "Generator.h"
#include "Loader.h"
#include "Worker.h"

using namespace wfe;

int main(int argc, char *argv[])
{
	ConcurrentWorkflowExecutor exec(4);
	Director d(&exec);

	Generator g1(1);
	Loader l1(4);
	Worker w1;
	Worker w2;
	Worker w3;
	Worker w4;
	ManagerActor a1(&w1);
	ManagerActor a2(&w2);
	ManagerActor a3(&w3);
	ManagerActor a4(&w4);

	Channel *ch1 = d.createChannel();
	Channel *ch2 = d.createChannel();
	Channel *ch3 = d.createChannel();
	Channel *ch4 = d.createChannel();
	Channel *ch5 = d.createChannel();

	g1.sourcePorts()[0]->setChannel(ch1);
	a1.sinkPorts()[0]->setChannel(ch1);
	a2.sinkPorts()[0]->setChannel(ch1);
	a3.sinkPorts()[0]->setChannel(ch1);
	a4.sinkPorts()[0]->setChannel(ch1);
	a1.sourcePorts()[0]->setChannel(ch2);
	a2.sourcePorts()[0]->setChannel(ch3);
	a3.sourcePorts()[0]->setChannel(ch4);
	a4.sourcePorts()[0]->setChannel(ch5);


	l1.sinkPorts()[0]->setChannel(ch2);
	l1.sinkPorts()[1]->setChannel(ch3);
	l1.sinkPorts()[2]->setChannel(ch4);
	l1.sinkPorts()[3]->setChannel(ch5);

	d.addActor(&g1);
	d.addActor(&l1);
	d.addActor(&a1);
	d.addActor(&a2);
	d.addActor(&a3);
	d.addActor(&a4);

	Master::instance()->init(argc, argv);
	d.execute(5566, 7788);

	return 0;
}
