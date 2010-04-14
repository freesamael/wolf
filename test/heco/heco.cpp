///*
// * heco.cpp
// *
// *  Created on: Apr 7, 2010
// *      Author: samael
// */
//
//#include <Director.h>
//#include <SimpleWorkflowExecutor.h>
//#include <SimpleManagerWorkerExecutor.h>
//#include <RunnerAgent.h>
//#include "RandomNumberGeneratorActor.h"
//#include "NumberReaderActor.h"
//#include "NumberSubstractorManager.h"
//
//using namespace wfe;
//
//int main()
//{
//	SimpleManagerWorkerExecutor mwexec;
//	SimpleWorkflowExecutor exec;
//	Director d(&exec);
//
//	RandomNumberGeneratorActor *a1 = new RandomNumberGeneratorActor();
//	NumberSubstractorManager *a2 = new NumberSubstractorManager(&mwexec);
//	NumberReaderActor *a3 = new NumberReaderActor();
//	d.addActor(a1);
//	d.addActor(a2);
//	d.addActor(a3);
//
//	Channel *c1 = d.createChannel("ch1");
//	Channel *c2 = d.createChannel("ch2");
//	a1->outports()[0]->setChannel(c1);
//	a2->inports()[0]->setChannel(c1);
//	a2->outports()[0]->setChannel(c2);
//	a3->inports()[0]->setChannel(c2);
//
//	RunnerAgent::instance()->setup(6655, 8877, "heco");
//
//	d.execute();
//
//	return 0;
//}
