/**
 * \file heco.cpp
 * \date Jun 20, 2010
 * \author samael
 */

#include <vector>
#include <ConcurrentWorkflowExecutor.h>
#include <Director.h>
#include <ManagerActor.h>
#include <Master.h>
#include "Generator.h"
#include "Loader.h"
#include "Worker.h"

using namespace std;
using namespace wfe;

int main(int argc, char *argv[])
{
	ConcurrentWorkflowExecutor exec(60);
	Director d(&exec);

	vector<Worker *> workers;
	vector<ManagerActor *> managers;

	Generator gtr(1);
	d.addActor(&gtr);

	Loader ldr(60);
	d.addActor(&ldr);

	// Setup first port.
	Channel *ch1 = d.createChannel();
	gtr.sourcePorts()[0]->setChannel(ch1);

	for (int i = 0; i < 60; i++) {
		Worker *w = new Worker();
		ManagerActor *m = new ManagerActor(w);
		d.addActor(m);

		// Setup all intermediate ports.
		Channel *ich = d.createChannel();
		m->sinkPorts()[0]->setChannel(ch1);
		m->sourcePorts()[0]->setChannel(ich);
		ldr.sinkPorts()[i]->setChannel(ich);

		workers.push_back(w);
		managers.push_back(m);
	}

	Master::instance()->init(argc, argv);
	d.execute(5566, 7788);

	// Cleanup.
	for (int i = 0; i < 60; i++) {
		delete managers[i];
		delete workers[i];
	}

	return 0;
}
