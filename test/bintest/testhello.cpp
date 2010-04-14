/**
 * \file testhello.cpp
 * \date Apr 14, 2010
 * \author samael
 */

#include <iostream>
#include <Director.h>
#include <AbstractActor.h>
#include <SimpleWorkflowExecutor.h>

using namespace std;
using namespace wfe;

class HelloActor: public AbstractActor
{
public:
	HelloActor(): _state(READY) {}
	State state() { return _state; }
	void fire() { cout << "Hello World!" << endl; }
	void wrapup() { _state = FINISHED; }

private:
	State _state;
};

int main()
{
	SimpleWorkflowExecutor exec;
	Director d(&exec);
	HelloActor hello;

	d.addActor(&hello);
	d.execute();

	return 0;
}
