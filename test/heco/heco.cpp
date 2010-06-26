/**
 * \file heco.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <vector>
#include <SimpleWorkflowExecutor.h>
#include <AlwaysFirstWorkerDispatcher.h>
#include <Director.h>
#include <SimpleManagerActor.h>
#include <Master.h>
#include "Generator.h"
#include "Loader.h"
#include "Worker.h"

using namespace std;
using namespace wfe;

int main(int argc, char *argv[])
{
	AlwaysFirstWorkerDispatcher disp;
	Master::instance()->init(argc, argv);
	Master::instance()->setDispatcher(&disp);

//	ConcurrentWorkflowExecutor exec(60);
	SimpleWorkflowExecutor exec;
	Director d(&exec);

	vector<Worker *> workers;
	vector<SimpleManagerActor *> managers;

	Generator gtr(1);
	d.addActor(&gtr);

	Loader ldr(60);
	d.addActor(&ldr);

	// Setup first port.
	Channel *ch1 = d.createChannel();
	gtr.sourcePorts()[0]->setChannel(ch1);

	for (int i = 0; i < 60; i++) {
		Worker *w = new Worker();
		SimpleManagerActor *m = new SimpleManagerActor(w);
		d.addActor(m);

		// Setup all intermediate ports.
		Channel *ich = d.createChannel();
		m->sinkPorts()[0]->setChannel(ch1);
		m->sourcePorts()[0]->setChannel(ich);
		ldr.sinkPorts()[i]->setChannel(ich);

		workers.push_back(w);
		managers.push_back(m);
	}

	d.execute(5566, 7788);

	// Cleanup.
	for (int i = 0; i < 60; i++) {
		delete managers[i];
		delete workers[i];
	}

	return 0;
}
