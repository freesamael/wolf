/**
 * \file hecodsm.cpp
 * \date Apr 7, 2010
 * \author samael
 */

#include <CDirector.h>
#include <CSimpleWorkflowExecutor.h>
#include <CSimpleManagerActor.h>
#include "HecoDataGenerator.h"
#include "HecoFinalizer.h"
#include "HecoWorker.h"
#include "HecoWorkerCreator.h"

using namespace wfe;

int main()
{
	CSimpleWorkflowExecutor exec;
	CDirector d(&exec);

	HecoDSMDataGenerator a1;
	HecoDSMWorker w1;
	CSimpleManagerActor a2(&w1);
	HecoDSMFinalizer a3;
	CChannel *ch1 = d.createChannel();
	CChannel *ch2 = d.createChannel();

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
