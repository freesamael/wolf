/*
 * main.cpp
 *
 *  Created on: Mar 22, 2010
 *      Author: samael
 */

#include <iostream>
#include <Channel.h>
#include <Director.h>
#include <Port.h>
#include <SimpleWorkflowExecutor.h>
#include <SimpleManagerWorkerExecutor.h>
#include <AbstractManagerActor.h>

using namespace std;
using namespace cml;
using namespace wfe;

class FirstActor: public IActor, public ISourceComponent
{
public:
	FirstActor(): _state(NOT_READY) {
		_outports.push_back(new Port(this));
	}
	const vector<Port *>& outports() { return _outports; }
	State state() {
		if (_state == NOT_READY)
			_state = READY;
		cout << "FirstActor: " << StateString[_state] << endl;
		return _state;
	}
	void prefire() { _state = RUNNING; }
	void fire() {
		cout << "FirstActor: Fire." << endl;
		_outports[0]->channel()->setSharedMemory((SharedMemory *)1);
	}
	void postfire() { _state = FINISHED; }
	void reset() { _state = NOT_READY; }
private:
	IActor::State _state;
	vector<Port *> _outports;
};

class LastActor: public IActor, public ISinkComponent
{
public:
	LastActor(): _state(NOT_READY) {
		_inports.push_back(new Port(this));
	}
	const vector<Port *>& inports() { return _inports; }
	State state() {
		if (_state == NOT_READY)
			if (_inports[0]->channel()->state() == Channel::WRITTEN)
				_state = READY;
		cout << "LastActor: " << StateString[_state] << endl;
		return _state;
	}
	void prefire() { _state = RUNNING; }
	void fire() { cout << "LastActor: Fire." << endl; }
	void postfire() { _state = FINISHED; }
	void reset() { _state = NOT_READY; }
private:
	IActor::State _state;
	vector<Port *> _inports;
};

class TestActor: public AbstractManagerActor
{
public:
	TestActor(IManagerWorkerExecutor *exec, const string &name):
		AbstractManagerActor(exec), _name(name) {
		_inports.push_back(new Port(this));
		_outports.push_back(new Port(this));
	}
	State state() {
		if (_state == NOT_READY)
			if (isInputReady())
				_state = READY;
		cout << _name << ": " << StateString[_state] << endl;
		return _state;
	}
	void prefire() { _state = RUNNING; }
	void fire() {
		cout << _name << ": Fire." << endl;
		_outports[0]->channel()->setSharedMemory((SharedMemory*)1);
	}
	void postfire() { _state = FINISHED; }
	void reset() { _state = NOT_READY; }

private:
	string _name;
};

int main()
{
	SimpleWorkflowExecutor workflowexec;
	SimpleManagerWorkerExecutor manwokexec;
	Director d(&workflowexec);

	// Create actors.
	FirstActor *fa = new FirstActor();
	LastActor *la = new LastActor();
	TestActor *t1 = new TestActor(&manwokexec, "Actor 1"),
			*t2 = new TestActor(&manwokexec, "Actor 2"),
			*t3 = new TestActor(&manwokexec, "Actor 3"),
			*t4 = new TestActor(&manwokexec, "Actor 4");

	// Add actors.
	d.addActor(fa);
	d.addActor(t1);
	d.addActor(t2);
	d.addActor(t3);
	d.addActor(t4);
	d.addActor(la);

	// Create channels.
	Channel *c0 = d.createChannel("ch0");
	Channel *c1 = d.createChannel("ch1");
	Channel *c2 = d.createChannel("ch2");
	Channel *c3 = d.createChannel("ch3");
	Channel *c4 = d.createChannel("ch4");

	// Attach channels.
	fa->outports()[0]->setChannel(c0);
	t1->inports()[0]->setChannel(c0);
	t1->outports()[0]->setChannel(c1);
	t2->inports()[0]->setChannel(c1);
	t2->outports()[0]->setChannel(c2);
	t3->inports()[0]->setChannel(c2);
	t3->outports()[0]->setChannel(c3);
	t4->inports()[0]->setChannel(c3);
	t4->outports()[0]->setChannel(c4);
	la->inports()[0]->setChannel(c4);

	d.execute();

	return 0;
}
