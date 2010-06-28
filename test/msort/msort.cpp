/**
 * \file msort.cpp
 * \date Jun 28, 2010
 * \author samael
 */
#include <Director.h>
#include <SimpleWorkflowExecutor.h>
#include <AlwaysFirstWorkerDispatcher.h>
#include <Master.h>
#include <SimpleManagerActor.h>
#include "MSortDataGenerator.h"
#include "MSortFinalizer.h"
#include "MSortWorker.h"

using namespace std;
using namespace cml;
using namespace wfe;

#define NWORKERS	16

int main(int argc, char *argv[])
{
	Master::instance()->init(argc, argv);
	AlwaysFirstWorkerDispatcher disp;
	Master::instance()->setDispatcher(&disp);

	SimpleWorkflowExecutor exec;
	Director d(&exec);

	vector<MSortWorker *> wrks;
	vector<SimpleManagerActor *> mgrs;

	MSortDataGenerator gen(NWORKERS, 8000);
	d.addActor(&gen);

	MSortFinalizer fin(NWORKERS);
	d.addActor(&fin);

	for (int i = 0; i < NWORKERS; i++) {
		MSortWorker *w = new MSortWorker();
		SimpleManagerActor *m = new SimpleManagerActor(w);
		d.addActor(m);

		// Setup input channel for worker.
		Channel *c = d.createChannel();
		gen.sourcePorts()[i]->setChannel(c);
		m->sinkPorts()[0]->setChannel(c);

		// Setup output channel for worker.
		c = d.createChannel();
		m->sourcePorts()[0]->setChannel(c);
		fin.sinkPorts()[i]->setChannel(c);

		wrks.push_back(w);
		mgrs.push_back(m);
	}

	d.execute(9527, 7259);

	for (int i = 0; i < NWORKERS; i++) {
		delete mgrs[i];
		delete wrks[i];
	}

	cout << "Total Execution time = " << Master::instance()->executionTime() <<
			endl;

	return 0;
}
