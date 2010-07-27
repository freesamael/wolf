/**
 * \file msort.cpp
 * \date Jun 28, 2010
 * \author samael
 */
#include <CDirector.h>
#include <CSimpleWorkflowExecutor.h>
#include <CAlwaysFirstWorkerDispatcher.h>
#include <CMaster.h>
#include <CSimpleManagerActor.h>
#include "MSortDataGenerator.h"
#include "MSortFinalizer.h"
#include "MSortWorker.h"

using namespace std;
using namespace wolf;
using namespace wolf;

#define NWORKERS	10
#define NSIZE		120

int main(int argc, char *argv[])
{
	CMaster::instance()->init(argc, argv);
	CAlwaysFirstWorkerDispatcher disp;
	CMaster::instance()->setDispatcher(&disp);

	CSimpleWorkflowExecutor exec;
	CDirector d(&exec);

	vector<MSortWorker *> wrks;
	vector<CSimpleManagerActor *> mgrs;

	MSortDataGenerator gen(NWORKERS, NSIZE);
	d.addActor(&gen);

	MSortFinalizer fin(NWORKERS);
	d.addActor(&fin);

	for (int i = 0; i < NWORKERS; i++) {
		MSortWorker *w = new MSortWorker();
		CSimpleManagerActor *m = new CSimpleManagerActor(w);
		d.addActor(m);

		// Setup input channel for worker.
		CChannel *c = d.createChannel();
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

	cout << "Total Execution Time = " << CMaster::instance()->executionTime() <<
			endl;

	return 0;
}
