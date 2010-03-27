/*
 * main.cpp
 *
 *  Created on: Mar 22, 2010
 *      Author: samael
 */

#include <iostream>
#include "AbstractActor.h"
#include "Channel.h"
#include "Director.h"
#include "Port.h"
#include "SimpleExecutionStrategy.h"

using namespace std;
using namespace cml;
using namespace wfe;

class TestActor: public AbstractActor
{
public:
	TestActor(const string &name): _name(name) {
		_inports.push_back(new Port(this));
		_outports.push_back(new Port(this));
	}
	void fire() {
		cout << _name << ": Fire." << endl;
		_outports[0]->channel()->write((SharedMemory*)1);
	}
	ActorState state() {
		AbstractActor::state();
		string state = (_state == READY) ? "READY" : "WAITING";
		cout << _name << ": State: " << state << endl;
		return _state;
	}

private:
	string _name;
};

int main()
{
	SimpleExecutionStrategy exest;
	Director d(&exest);
	TestActor *t1 = new TestActor("Actor 1"), *t2 = new TestActor("Actor 2"),
			*t3 = new TestActor("Actor 3"), *t4 = new TestActor("Actor 4");

	// Add actors.
	d.addActor(t1);
	d.addActor(t2);
	d.addActor(t3);
	d.addActor(t4);

	// Create channels.
	Channel *c0 = d.createChannel("ch0");
	Channel *c1 = d.createChannel("ch1");
	Channel *c2 = d.createChannel("ch2");
	Channel *c3 = d.createChannel("ch3");
	Channel *c4 = d.createChannel("ch4");

	// Attach channels.
	t1->attachChannel(t1->inputPorts()[0], c0);
	t1->attachChannel(t1->outputPorts()[0], c1);
	t2->attachChannel(t2->inputPorts()[0], c1);
	t2->attachChannel(t2->outputPorts()[0], c2);
	t3->attachChannel(t3->inputPorts()[0], c2);
	t3->attachChannel(t3->outputPorts()[0], c3);
	t4->attachChannel(t4->inputPorts()[0], c3);
	t4->attachChannel(t4->outputPorts()[0], c4);

	// Write ch0.
	c0->write((SharedMemory*)1);

	d.execute();

	return 0;
}
