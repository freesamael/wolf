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
#include "HecoDataGenerator.h"
#include "HecoFinalizer.h"
#include "HecoWorker.h"

using namespace std;
using namespace wfe;

#define NWORKER	600

int main(int argc, char *argv[])
{
	AlwaysFirstWorkerDispatcher disp;
	Master::instance()->init(argc, argv);
	Master::instance()->setDispatcher(&disp);

	SimpleWorkflowExecutor exec;
	Director d(&exec);

	vector<HecoWorker *> workers;
	vector<SimpleManagerActor *> managers;

	HecoDataGenerator gtr(1);
	d.addActor(&gtr);

	HecoFinalizer ldr(NWORKER);
	d.addActor(&ldr);

	// Setup first port.
	Channel *ch1 = d.createChannel();
	gtr.sourcePorts()[0]->setChannel(ch1);

	for (int i = 0; i < NWORKER; i++) {
		HecoWorker *w = new HecoWorker();
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
	for (int i = 0; i < NWORKER; i++) {
		delete managers[i];
		delete workers[i];
	}

	return 0;
}
