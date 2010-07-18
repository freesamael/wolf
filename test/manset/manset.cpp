/**
 * \file manset.cpp
 * \date Jul 16, 2010
 * \author samael
 */

#include <vector>
#include <CMaster.h>
#include <CDirector.h>
#include <CSimpleManagerActor.h>
#include <CSimpleWorkflowExecutor.h>
#include "MansetConfigGenerator.h"
#include "MansetWorker.h"
#include "MansetFinalizer.h"

using namespace std;
using namespace wfe;

#define IMG_WIDTH	300
#define IMG_HEIGHT	240
#define IMG_ROWS	40

int main(int argc, char *argv[])
{
	CMaster::instance()->init(argc, argv);

	CSimpleWorkflowExecutor exec;
	CDirector d(&exec);
	MansetConfigGenerator gen(IMG_WIDTH, IMG_HEIGHT, IMG_ROWS);
	MansetFinalizer fin(IMG_WIDTH, IMG_HEIGHT, IMG_ROWS);
	vector<CSimpleManagerActor *> _mgrs;
	vector<MansetWorker *> _wrks;

	d.addActor(&gen);
	d.addActor(&fin);
	for (int i = 0; i < IMG_HEIGHT / IMG_ROWS; i++) {
		MansetWorker *w = new MansetWorker();
		CSimpleManagerActor *m = new CSimpleManagerActor(w);
		CChannel *in = d.createChannel();
		CChannel *out = d.createChannel();

		gen.sourcePorts()[i]->setChannel(in);
		m->sinkPorts()[0]->setChannel(in);
		m->sourcePorts()[0]->setChannel(out);
		fin.sinkPorts()[i]->setChannel(out);

		d.addActor(m);
		_mgrs.push_back(m);
		_wrks.push_back(w);
	}

	d.execute(5566, 7788);

	for (unsigned i = 0; i < _mgrs.size(); i++) {
		delete _mgrs[i];
		delete _wrks[i];
	}

	return 0;
}